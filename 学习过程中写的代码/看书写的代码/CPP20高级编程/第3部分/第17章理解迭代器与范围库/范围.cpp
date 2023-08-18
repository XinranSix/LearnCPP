#include <algorithm>
#include <format>
#include <string_view>
#include <iostream>
#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <ranges>

TEST(范围, 基于范围的算法1) {
    std::vector data { 33, 11, 22 };
    std::sort(begin(data), end(data));
    std::ranges::sort(data);
}

class Person {
public:
    Person(std::string first, std::string last) : m_firstName { first }, m_lastName { last } {}

    std::string const &getFirstName() const {
        return m_firstName;
    }

    std::string const &getLastName() const {
        return m_lastName;
    }

private:
    std::string m_firstName;
    std::string m_lastName;
};

TEST(范围, 基于范围的算法2) {
    std::vector persons { Person { "John", "White" }, Person { "Chris", "Blue" } };
    std::ranges::sort(persons, {}, [](Person const &person) { return person.getFirstName(); });
    std::ranges::sort(persons, {}, &Person::getFirstName);
}

void printRange(std::string_view message, auto &range) {
    std::cout << message;
    for (auto const &value : range) {
        std::cout << value << ' ';
    }
    std::cout << std::endl;
}

TEST(范围, 视图) {
    std::vector values { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    printRange("Original: ", values);

    auto result1 { values | std::views::filter([](auto const &value) { return value % 2 == 0; }) };
    printRange("Only even values: ", result1);

    auto result2 { result1 | std::views::transform([](auto const &value) { return value * 2.0; }) };
    printRange("Values doubled: ", result2);

    auto result3 { result2 | std::views::drop(2) };
    printRange("First two dropped: ", result3);

    auto result4 { result3 | std::views::reverse };
    printRange("Sequence reversed: ", result4);

    auto result { values | std::views::filter([](auto const &value) { return value % 2 == 0; }) |
                  std::views::transform([](auto const &value) { return value * 2.0; }) |
                  std::views::drop(2) | std::views::reverse };
    printRange("Final sequence: ", result);
}

TEST(范围, 通过视图修改元素) {
    std::vector values { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    printRange("Original sequence: ", values);

    auto result1 { values | std::views::filter([](auto const &value) { return value % 2 == 0; }) };
    printRange("Only even values: ", result1);

    auto result2 { values | std::views::drop(2) };
    printRange("First two dropped: ", result2);

    auto result3 { result2 | std::views::reverse };
    printRange("Sequence reversed: ", result3);

    for (auto &value : result3) {
        value *= 10;
    }
    printRange("After modifying elements through a view, vector, contains: ", values);
}

TEST(范围, 映射元素) {
    std::vector values { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    printRange("Original sequence: ", values);

    auto result { values | std::views::filter([](auto const &value) { return value % 2 == 0; }) |
                  std::views::take(3) |
                  std::views::transform([](auto const &v) { return std::format(R"("{}")", v); }) };
    printRange("Result: ", result);
}

TEST(范围, 范围工厂) {
    auto values { std::views::iota(10) };
    auto result { values | std::views::filter([](auto const &value) { return value % 2 == 0; }) |
                  std::views::transform([](auto const &value) { return value * 2.0; }) |
                  std::views::take(10) };

    printRange("Result: ", result);
}

TEST(范围, 输入流作为视图) {
    for (auto value : std::ranges::istream_view<int>(std::cin) |
                          std::views::take_while([](auto const &v) { return v < 5; }) |
                          std::views::transform([](auto const &v) { return v * 2; })) {
        std::cout << std::format("> {}\n", value) << std::endl;
    }
    std::cout << "Terminating..." << std::endl;
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

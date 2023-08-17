#include <concepts>
#include <functional>
#include <iostream>
#include <gtest/gtest.h>
#include <format>
#include <memory>
#include <span>
#include <string_view>
#include <type_traits>

void func(int num, std::string_view str) {
    std::cout << std::format("func({}, {})", num, str) << std::endl;
}

void findMatches(std::span<const int> values1, std::span<const int> values2, auto matcher,
                 auto matcherHandler) {
    if (values1.size() != values2.size()) {
        return;
    }

    for (size_t i { 0 }; i < values1.size(); ++i) {
        if (matcher(values1[i], values2[i])) {
            matcherHandler(i, values1[i], values2[i]);
        }
    }
}

void printMatch(size_t position, int value1, int value2) {
    std::cout << std::format("Match found at position {}({}, {})", position, value1, value2)
              << std::endl;
}

bool intEqual(int item1, int item2) {
    return item1 == item2;
}

TEST(lambda表达式, 语法) {
    auto basicLambda { [] { std::cout << "Hello form Lambda" << std::endl; } };
    basicLambda();

    auto parametersLambda([](int value) { std::cout << "The value is " << value << std::endl; });
    parametersLambda(42);

    // auto returningLambda { [](int a, int b) -> int { return a + b; } };
    auto returningLambda { [](int a, int b) { return a + b; } };
    int sum { returningLambda(11, 22) };
}

class Person {
public:
    Person(std::string name) : m_name { std::move(name) } {}

    std::string const &getName() const {
        return m_name;
    }

private:
    std::string m_name;
};

TEST(lambda表达式, 保留cv限定符) {
    [](Person const &person) -> decltype(auto) { return person.getName(); };
}

TEST(lambda表达式, 捕获变量) {
    double data { 1.23 };
    // auto capturingLambda { [data] { std::cout << "Data = " << data << std::endl; } };
    // auto capturingLambda { [data]() mutable { std::cout << "Data = " << data << std::endl; } };
    auto capturingLambda { [&data]() { data *= 2; } };
}

TEST(lambda表达式, lambda表达式作为参数) {
    std::vector values1 { 2, 5, 6, 9, 10, 1, 1 };
    std::vector values2 { 4, 4, 2, 9, 0, 3, 1 };
    findMatches(
        values1, values2, [](int value1, int value2) { return value1 == value2; }, printMatch);
}

TEST(lambda表达式, 泛型lambda表达式) {
    auto areEqual { [](auto const &value1, auto const &value2) { return value1 == value2; } };
    std::vector values1 { 2, 5, 6, 9, 10, 1, 1 };
    std::vector values2 { 4, 4, 2, 9, 0, 3, 1 };
    findMatches(values1, values2, areEqual, printMatch);
}

TEST(lambda表达式, lambda表达式捕获表达式) {
    double pi { 3.1415 };
    auto myLambda { [myCapture = "Pi: ", pi]() { std::cout << myCapture << pi << std::endl; } };
    myLambda();

    auto myPtr { std::make_unique<double>(3.1415) };
    auto myLambda1 { [p = std::move(myPtr)]() { std::cout << *p << std::endl; } };
    myLambda1();
}

TEST(lambda表达式, 模板化lambda表达式) {
    auto lambda { [](auto const &values) {
        using V = std::decay_t<decltype(values)>;
        using T = typename V::value_type;
        T someValue {};
        // T::som
    } };

    auto lambda1 = []<typename T>(std::vector<T> const &values) { T someValue {}; };

    auto lambda2 = []<typename T>(T const &value1, T const &value2)
        requires std::integral<T>
    {};
}

// std::function<int(void)> multiplyBy2Lambda(int x) {
auto multiplyBy2Lambda(int x) {
    return [x] { return 2 * x; };
}

TEST(lambda表达式, lambda表达式作为返回类型) {
    // std::function<int(void)> fn { multiplyBy2Lambda(5) };
    auto fn { multiplyBy2Lambda(5) };
    std::cout << fn() << std::endl;
}

TEST(lambda表达式, 未计算上下文的lambda表达式) {
    using LambdaType = decltype([](int a, int b) { return a + b; });
}

using LambdaType = decltype([](int a, int b) { return a + b; });

LambdaType getLambdaType() {
    return LambdaType {};
}

TEST(lambda表达式, 默认构造_拷贝和赋值) {
    auto lambda { [](int a, int b) { return a + b; } };
    decltype(lambda) lambda2;
    auto copy { lambda };
    copy = lambda2;
}

void printMessage(std::string_view message) {
    std::cout << message << std::endl;
}

TEST(lambda表达式, 调用) {
    std::invoke(printMessage, "Hello invoke.");
    std::invoke([](auto const &msg) { std::cout << msg << std::endl; }, "Hello invoke.");
    std::string msg { "Hello invoke." };
    std::cout << std::invoke(&std::string::size, msg) << std::endl;
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

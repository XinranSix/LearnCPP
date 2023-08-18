#include <cmath>
#include <functional>
#include <iostream>
#include <gtest/gtest.h>
#include <queue>
#include <vector>
#include <span>
#include <format>

bool intEqual(int item1, int item2) {
    return item1 == item2;
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

class IsLargerThan {
public:
    explicit IsLargerThan(int value) : m_value { value } {}

    bool operator()(int value1, int value2) const {
        return value1 > m_value && value2 > m_value;
    }

private:
    int m_value;
};

TEST(函数对象, 编写第一个函数对象) {
    std::vector values1 { 2, 500, 6, 9, 10, 101, 1 };
    std::vector values2 { 4, 5, 2, 9, 0, 300, 1 };

    findMatches(values1, values2, IsLargerThan { 100 }, printMatch);
}

template <typename Iter, typename StartValue, typename Operation>
auto accumulateData(Iter begin, Iter end, StartValue startValue, Operation op) {
    auto accumulated { startValue };
    for (Iter iter { begin }; iter != end; ++iter) {
        accumulated = op(accumulated, *iter);
    }
    return accumulated;
}

double geometricMean(std::span<const int> values) {
    auto mult { accumulateData(cbegin(values), cend(values), 1, std::multiplies<int> {}) };
    return std::pow(mult, 1.0 / values.size());
}

TEST(函数对象, 标准库中的函数对象之算术函数对象) {
    /*
    std::plus std::minus std::multiplies std::divides std::modulus
    std::negate
    */
    std::plus<int> myPlus;
    int res { myPlus(4, 5) };

    std::cout << res << std::endl;
}

double geometricMeanTransparent(std::span<const int> values) {
    auto mult { accumulateData(cbegin(values), cend(values), 1, std::multiplies<> {}) };
    return std::pow(mult, 1.0 / values.size());
}

TEST(函数对象, 标准库中的函数对象之透明运算符仿函数) {
    std::vector<int> values { 1, 2, 3 };
    double result { accumulateData(cbegin(values), cend(values), 1.1, std::multiplies<> {}) };
    std::cout << result << std::endl;

    double result1 { accumulateData(cbegin(values), cend(values), 1.1, std::multiplies<int> {}) };
    std::cout << result1 << std::endl;
}

TEST(函数对象, 标准库中的函数对象之比较函数对象) {
    // std::priority_queue<int> myQueue;
    std::priority_queue<int, std::vector<int>, std::greater<>> myQueue;
    myQueue.push(3);
    myQueue.push(4);
    myQueue.push(2);
    myQueue.push(1);
    while (!myQueue.empty()) {
        std::cout << myQueue.top() << ' ';
        myQueue.pop();
    }
    std::cout << std::endl;
}

bool allTrue(std::vector<bool> const &flags) {
    return accumulateData(begin(flags), end(flags), true, std::logical_and<> {});
}

TEST(函数对象, 标准库中的函数对象之逻辑函数对象) {}

TEST(函数对象, 标准库中的函数对象之位函数对象) {}

void func(int num, std::string_view str) {
    std::cout << std::format("func({}, {})", num, str) << std::endl;
}

void increment(int &value) {
    ++value;
}

TEST(函数对象, 适配器函数对象之绑定器) {
    std::string mtString { "abc" };
    auto f1 { std::bind(func, std::placeholders::_1, mtString) };
    f1(16);

    auto f2 { std::bind(func, std::placeholders::_2, std::placeholders::_1) };
    f2("Test", 32);

    int index { 0 };
    increment(index);

    auto incr1 { std::bind(increment, index) };
    incr1();
    auto incr2 { std::bind(increment, std::ref(index)) };
    incr2();
}

void overloaded(int num) {}
void overloaded(float f) {}

TEST(函数对象, 适配器函数对象之绑定器的重载问题) {
    // auto f3 { std::bind(overloaded, std::placeholders::_1) }; // Error
    auto f4 { std::bind((void (*)(float))overloaded, std::placeholders::_1) }; // Error
}

class Handler {
public:
    void handleMatch(size_t position, int value1, int value2) {
        std::cout << std::format("Match found at position {} ({}, {})", position, value1, value2);
    }
};

TEST(函数对象, 适配器函数对象之绑定器的绑定类成员函数的问题) {

    std::vector values1 { 2, 500, 6, 9, 10, 101, 1 };
    std::vector values2 { 4, 5, 2, 9, 0, 300, 1 };

    Handler handler;
    findMatches(values1, values2, intEqual,
                std::bind(&Handler::handleMatch, &handler, std::placeholders::_1,
                          std::placeholders::_2, std::placeholders::_3));
}

TEST(函数对象, 适配器函数对象之否定器) {
    std::vector values1 { 2, 500, 6, 9, 10, 101, 1 };
    std::vector values2 { 4, 5, 2, 9, 0, 300, 1 };

    findMatches(values1, values2, std::not_fn(intEqual), &printMatch);
}

template <typename Matcher>
void printMatchingStrings(std::vector<std::string> const &strings, Matcher matcher) {
    for (auto const &string : strings) {
        if (matcher(string)) {
            std::cout << string << " ";
        }
    }
}

TEST(函数对象, 调用成员函数) {
    std::vector<std::string> values { "Hello", "", "", "World", "!" };
    printMatchingStrings(values, std::not_fn(std::mem_fn(&std::string::empty)));
    std::cout << std::endl;
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

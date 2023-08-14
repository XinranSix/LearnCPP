#include <concepts>
#include <iostream>
#include <gtest/gtest.h>

template <typename T>
concept C = sizeof(T) == 4;

TEST(概念, 约束表达式) {
    // 约束表达式时一个 bool 类型的编译期求值的常量表达式
}

// 简单 requirement
template <typename T>
concept Incrementable = requires(T x) {
    // 验证类型 T 是否支持自增运算符
    x++;
    ++x;
};

// 类型 requirement
// 验证 T 是否有value_type 成员
template <typename T>
concept C1 = requires { typename T::value_type; };

template <typename T>
struct X {};

// 验证类模板 X 是否支持给定类型的实例化
template <typename T>
concept C2 = requires { typename X<T>; };

// 复合 requirement
// 可以用于验证某些东西不会抛出任何异常/或验证某个方法是否返回某个类型

// 验证给定类型是否具有标记为 noexcept 的 swap 方法
template <typename T>
concept C3 = requires(T x, T y) {
    { x.swap(y) } noexcept;
};

// 验证给定类型是否有一个 size() 函数，并且其返回值是否可以转换为 size_t 类型
template <typename T>
concept C4 = requires(const T x) {
    { x.size() } -> std::convertible_to<size_t>;
};

// 验证给定类型是否支持比较
template <typename T>
concept Comparable = requires(const T a, const T b) {
    { a == b } -> std::convertible_to<bool>;
    { a < b } -> std::convertible_to<bool>;
    { a > b } -> std::convertible_to<bool>;
    { a <= b } -> std::convertible_to<bool>;
    { a >= b } -> std::convertible_to<bool>;
    { a != b } -> std::convertible_to<bool>;
};

// 嵌套 requirement
// 懒得写了
template <typename T>
concept C5 = requires(T t) {
    requires sizeof(T) == 4;
    ++t;
    --t;
    t++;
    t--;
};

TEST(概念, require表达式) {
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

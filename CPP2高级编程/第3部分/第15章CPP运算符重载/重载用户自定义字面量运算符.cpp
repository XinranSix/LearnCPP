#include <cstddef>
#include <iostream>
#include <gtest/gtest.h>
#include <string>

template <typename T>
struct complex {
    complex(T, T) {}
};

complex<long double> operator""_i(long double d) {
    return complex<long double> { 0, d };
}

std::string operator""_s(const char *str, size_t len) {
    return std::string(str, len);
}

TEST(重载用户自定义字面量运算符, cooked模式字面量运算符) {
    complex<long double> c1 { 9.634_i };
    auto c2 { 1.23_i };

    std::string str1 { "Hello World"_s };
    auto str2 { "Hello World"_s };
    auto str3 { "Hello World" };
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

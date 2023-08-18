#include <iostream>
#include <gtest/gtest.h>
#include <ratio>
#include <format>

TEST(编译器有理数, 定义有理数) {
    /*
    num = sign(n) * sign(d) * abs(n) / gcd
    dec = abs(d) / gcd
    */
    using r1 = std::ratio<1, 60>;

    std::intmax_t num { r1::num };
    std::intmax_t den { r1::den };

    const std::intmax_t n { 1 };
    const std::intmax_t d { 1 };
    using r2 = std::ratio<n, d>;
}

TEST(编译器有理数, 有理数的运算) {
    /*
    算术运算，返回一个新的 ratio 类型：ratio_add ratio_subtract ratio_multiply ratio_divide
    比较运算，返回一个 std::bool_constant 类型：ratio_equal ratio_not_equal ratio_less
    ratio_less_equal ratio_greater rario_greater_equal
    */
    using r1 = std::ratio<1, 60>;
    std::intmax_t num { r1::num };
    std::intmax_t den { r1::den };
    std::cout << std::format("1) r1 = {}/{}", num, den) << std::endl;


    using r2 = std::ratio<1, 30>;
    
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

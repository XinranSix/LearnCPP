#include <cstdint>
#include <format>
#include <iostream>
#include <gtest/gtest.h>
#include <numbers>
#include <bit>
#include <ostream>
#include <utility>

TEST(CPP标准库概述, 数学工具) {
    // 数学常量
    std::cout << std::numbers::pi << std::endl;
    std::cout << std::numbers::inv_pi << std::endl;
    std::cout << std::numbers::sqrt2 << std::endl;
    std::cout << std::numbers::e << std::endl;
    std::cout << std::numbers::phi << std::endl;
    std::cout << std::endl;

    // 处理位的函数
    std::cout << std::format("std::has_single_bit(0U): {}", std::has_single_bit(0U)) << std::endl;
    std::cout << std::format("std::has_single_bit(1U): {}", std::has_single_bit(1U)) << std::endl;
    std::cout << std::format("std::has_single_bit(2U): {}", std::has_single_bit(2U)) << std::endl;
    std::cout << std::format("std::has_single_bit(3U): {}", std::has_single_bit(3U)) << std::endl;
    std::cout << std::format("std::has_single_bit(4U): {}", std::has_single_bit(4U)) << std::endl;
    std::cout << std::format("std::has_single_bit(5U): {}", std::has_single_bit(5U)) << std::endl;
    std::cout << std::format("std::has_single_bit(6U): {}", std::has_single_bit(6U)) << std::endl;
    std::cout << std::format("std::has_single_bit(7U): {}", std::has_single_bit(7U)) << std::endl;
    std::cout << std::format("std::has_single_bit(8U): {}", std::has_single_bit(8U)) << std::endl;

    std::cout << std::endl;

    std::cout << std::format("std::bit_ceil(0U): {}", std::bit_ceil(0U)) << std::endl;
    std::cout << std::format("std::bit_ceil(1U): {}", std::bit_ceil(1U)) << std::endl;
    std::cout << std::format("std::bit_ceil(3U): {}", std::bit_ceil(3U)) << std::endl;

    std::cout << std::endl;

    std::cout << std::format("std::bit_floor(0U): {}", std::bit_floor(0U)) << std::endl;
    std::cout << std::format("std::bit_floor(1U): {}", std::bit_floor(1U)) << std::endl;
    std::cout << std::format("std::bit_floor(2U): {}", std::bit_floor(2U)) << std::endl;
    std::cout << std::format("std::bit_floor(3U): {}", std::bit_floor(3U)) << std::endl;
    std::cout << std::format("std::bit_floor(4U): {}", std::bit_floor(4U)) << std::endl;
    std::cout << std::format("std::bit_floor(5U): {}", std::bit_floor(5U)) << std::endl;

    std::cout << std::endl;

    std::cout << std::format("std::bit_width(0U): {}", std::bit_width(0U)) << std::endl;
    std::cout << std::format("std::bit_width(1U): {}", std::bit_width(1U)) << std::endl;
    std::cout << std::format("std::bit_width(2U): {}", std::bit_width(2U)) << std::endl;
    std::cout << std::format("std::bit_width(3U): {}", std::bit_width(3U)) << std::endl;
    std::cout << std::format("std::bit_width(4U): {}", std::bit_width(4U)) << std::endl;
    std::cout << std::format("std::bit_width(5U): {}", std::bit_width(5U)) << std::endl;

    std::cout << std::endl;

    std::cout << std::popcount(0b10101010u) << std::endl;

    uint8_t value { 0b11101011u };
    std::cout << std::countl_one(value) << std::endl;
    std::cout << std::countr_one(value) << std::endl;

     value = 0b10001000;
    std::cout << std::format("{:08b}", std::rotl(value, 2)) << std::endl;

    std::cout << std::format("{}", std::cmp_greater(-1, 0u)) << std::endl;
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

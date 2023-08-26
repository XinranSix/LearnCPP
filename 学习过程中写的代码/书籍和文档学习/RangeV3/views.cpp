#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include "fmt/core.h"
#include "range/v3/view/addressof.hpp"
#include "range/v3/view/adjacent_filter.hpp"
#include "range/v3/view/adjacent_remove_if.hpp"
#include "range/v3/view/all.hpp"
#include "range/v3/view/filter.hpp"
#include "range/v3/view/any_view.hpp"
#include "range/v3/view/c_str.hpp"
#include "range/v3/view/cache1.hpp"
#include "range/v3/view/cartesian_product.hpp"
#include "range/v3/view/chunk.hpp"
#include "range/v3/view/common.hpp"
#include "range/v3/view/concat.hpp"
#include "range/v3/view/const.hpp"
#include "range/v3/view/counted.hpp"
#include "range/v3/view/cycle.hpp"

void printRange(auto range) {
    for (auto i : range) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;
}

TEST(views, addressof) {

    std::vector<int> v { 1, 2, 3 };

    // 给定左值引用的源范围，返回一个新视图，该视图是每个左值引用的 std::addressof 的结果。
    printRange(v | ranges::views::addressof);
    std::cout << &v[0] << ' ' << &v[1] << ' ' << &v[2] << std::endl;
}

TEST(views, adjacent_filter) {

    std::vector<int> numbers { 1, 2, 3, 5, 8, 13, 21 };

    auto is_adjacent_sum_even { [](int a, int b) { return (a + b) % 2 == 0; } };

    // 从前往后看，没看看连续的两个，看看这两个是否符合二元谓词，如果符合则保留第二个，否则舍弃
    // 总是保留第一个
    auto filtered_view { numbers | ranges::views::adjacent_filter(is_adjacent_sum_even) };

    printRange(filtered_view);
}

TEST(views, adjacent_remove_if) {
    std::vector<int> numbers { 1, 2, 3, 5, 8, 13, 21 };

    auto is_adjacent_sum_even { [](int a, int b) { return (a + b) % 2 == 0; } };

    // 从前往后看，没看看连续的两个，看看这两个是否符合二元谓词，如果符合则移除第一个，否则保留
    // 总是保留最后一个
    auto filtered_view { numbers | ranges::views::adjacent_remove_if(is_adjacent_sum_even) };

    printRange(filtered_view);
}

TEST(views, all) {
    std::vector<int> numbers { 1, 2, 3, 4, 5 };

    // Return a range containing all the elements in the source. Useful for converting containers to
    // ranges.
    auto all_view { numbers | ranges::views::all };

    printRange(all_view);
}

TEST(views, any_view) {
    std::vector<int> numbers { 1, 2, 3, 4, 5 };

    // Type-erased range of elements with value type T; can store any range with this value type.
    auto view { ranges::any_view<int>(numbers) }; // 创建范围视图

    printRange(view);

    auto result { view | ranges::views::transform([](int x) { return x * 2; }) |
                  ranges::views::filter([](int x) { return x > 5; }) };

    printRange(result);
}

// FIXME: 有问题
TEST(views, c_str) {
    // auto message = "Hello, ranges-v3!";

    // auto cstr_view = message | ranges::views::c_str; // 将字符串视为 C 风格字符串

    // // 使用 c_str_view 可以将字符串作为 C 风格字符串处理
    // std::cout << "C-Style String: " << cstr_view << std::endl;
}

// Caches the most recent element within the view so that dereferencing the view's iterator multiple
// times doesn't incur any recomputation. This can be useful in adaptor pipelines that include
// combinations of view::filter and view::transform, for instance. views::cache1 is always
// single-pass.
TEST(views, cache1) {
    std::vector<int> numbers { 1, 2, 3, 4, 5 };

    auto cached_view { numbers | ranges::views::cache1 }; // 使用 cache 视图

    for (int i = 0; i < 3; ++i) {
        printRange(cached_view);
    }
}

// 枚举 n 范围的 n 元笛卡尔积，即生成所有 n-元组 (e1, e2, ... , en) ，其中 e1 是枚举 n 范围的 n
// 元笛卡尔积，即生成所有 n -元组 (e1, e2, ... , en) ，其中 e1 是第一个范围， e2
// 是第二个范围的元素，依此类推。第一个范围， e2 是第二个范围的元素，依此类推。
TEST(views, cartesian_product) {

    std::vector<int> numbers { 1, 2 };
    std::vector<char> letters { 'A', 'B' };

    auto product_view { ranges::views::cartesian_product(numbers, letters) };

    for (const auto &tuple : product_view) {

        auto [num, letter] { tuple };

        std::cout << num << " " << letter << std::endl;
    }
}

// Given a source range and an integer N, produce a range of contiguous ranges where each inner
// range has N contiguous elements. The final range may have fewer than N elements.
TEST(views, chunk) {
    std::vector<int> numbers { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    auto chunked_view { numbers | ranges::views::chunk(3) }; // 将范围分割成大小为3的块

    for (const auto &chunk : chunked_view) {
        for (int value : chunk) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }
}

// FIXME: 不是很理解
TEST(views, common) {

    std::vector<int> numbers = { 1, 2, 3 };
    std::vector<double> floating_point_numbers = { 2.5, 3.7, 4.2 };

    auto mixed_view = ranges::views::concat(numbers, floating_point_numbers);

    auto common_view = mixed_view | ranges::views::common;

    printRange(common_view);
    printRange(mixed_view);
}

// Given N source ranges, produce a result range that is the concatenation of all of them.
TEST(views, concat) {
    std::vector<int> numbers = { 1, 2, 3 };
    std::vector<int> more_numbers = { 4, 5, 6 };
    std::vector<int> even_more_numbers = { 7, 8, 9 };

    auto concatenated_view = ranges::views::concat(numbers, more_numbers, even_more_numbers);

    printRange(concatenated_view);
}

// Present a const view of a source range.
TEST(views, const_) {
    std::vector<int> numbers = { 1, 2, 3, 4, 5 };

    auto const_view = numbers | ranges::views::const_; // 将范围中的元素视为常量

    // 修改范围中的元素值，会导致编译错误
    // const_view[2] = 99; // 这行会导致编译错误

    printRange(const_view);
}

// FIXME: 有问题
TEST(views, counted) {
    // std::vector<int> numbers = { 1, 2, 3, 4, 5 };

    // auto counted_view = numbers | ranges::views::counted(3); // 限制范围中的元素数量为3

    // for (int value : counted_view) {
    //     std::cout << value << " ";
    // }
}

// views::cycle
TEST(views, cycle) {
    std::vector<int> numbers = { 1, 2, 3 };

    auto cycle_view = numbers | ranges::views::cycle; // 创建一个无限循环的视图

    int count = 0;
    for (int value : cycle_view) {
        std::cout << value << " ";

        if (++count == 10) { // 限制遍历次数，否则会无限循环
            break;
        }
    }
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

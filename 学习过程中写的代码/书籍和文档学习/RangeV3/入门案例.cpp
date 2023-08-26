#include "fmt/core.h"
#include "range/v3/action/sort.hpp"
#include "range/v3/action/unique.hpp"
#include "range/v3/algorithm/for_each.hpp"
#include "range/v3/algorithm/sort.hpp"
#include "range/v3/range/conversion.hpp"
#include "range/v3/view/iota.hpp"
#include "range/v3/view/remove_if.hpp"
#include "range/v3/view/transform.hpp"
#include "range/v3/view/for_each.hpp"
#include "range/v3/view/addressof.hpp"
#include <iostream>
#include <gtest/gtest.h>

auto printRange(auto range) {
    ranges::for_each(range, [](auto v) { fmt::print("{} ", v); });
    fmt::print("\n");
}

TEST(入门案例, Convenience_便利) {
    std::vector<int> v { 2, 3, 1, 5, 1, 4 };
    ranges::sort(v);

    printRange(v);
}

TEST(入门案例, Composability_可组合性) {
    std::vector<int> const vi { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    auto rng { vi | ranges::views::remove_if([](int i) { return i % 2 == 1; }) |
               ranges::views::transform([](int i) { return std::to_string(i); }) };
    // rng == {"2","4","6","8","10"};

    printRange(rng);
}

TEST(入门案例, Composability_可组合性_actions) {
    std::vector<int> v { 2, 3, 1, 5, 1, 4 };
    // NOTE: rvalue | ranges::actions::算法 是可以的，而 lvalue 不行
    std::vector<int> vi =
        std::vector<int> { 2, 3, 1, 5, 1, 4 } | ranges::actions::sort | ranges::actions::unique;
    printRange(vi);
}

TEST(入门案例, Views_使用谓词过滤容器并对其进行转换) {
    std::vector<int> const vi { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    auto rng = vi | ranges::views::remove_if([](int i) { return i % 2 == 1; }) |
               ranges::views::transform([](int i) { return std::to_string(i); });
    // rng == {"2","4","6","8","10"};
    printRange(rng);
}

TEST(入门案例, Views_生成从1开始的无限整数列表对它们求平方取前10个并对它们求和) {
    auto vi = ranges::views::for_each(
                  ranges::views::ints(1, 10),
                  [](int i) { return ranges::yield_from(ranges::views::repeat_n(i, i)); }) |
              ranges::to<std::vector>();
    // vi == {1,2,2,3,3,3,4,4,4,4,5,5,5,5,5,...}
    printRange(vi);
}

// NOTE: 尽量使用非 const 的 views，在多线程中为了保证线程安全应该使用 views 的拷贝
// NOTE: 任何使迭代器失效的操作也会使 views 失效，因此应该在这种情况下重新获取视图

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

#include <format>
#include <iostream>
#include <gtest/gtest.h>
#include <functional>
#include <string_view>

void func(int num, std::string_view str) {
    std::cout << std::format("func({}, {})", num, str) << std::endl;
}

TEST(std__function, function实现函数指针) {
    // std::function<void(int, std::string_view)> f1 { func };
    std::function f1 { func };
    f1(1, "test");
}

// using Matcher = std::function<bool(int, int)>;
// using MatcherHandler = std::function<void(size_t, int, int)>;

// template <typename Matcher, typename MatchHandler>
// void findMatches(std::span<const int> values1, std::span<const int> values2, Matcher matcher,
//                  MatchHandler matcherHandler) {
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

bool intEqual(int item1, int item2) {
    return item1 == item2;
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

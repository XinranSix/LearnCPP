#include <iostream>
#include <gtest/gtest.h>

template <typename R, typename T1, typename T2>
R add(T1 const &t1, T2 const &t2) {
    return t1 + t2;
}

// 酱紫做是好的
template <typename T1, typename T2>
decltype(auto) add(T1 const &t1, T2 const &t2) {
    return t1 + t2;
}

// 不要酱紫
template <typename T1, typename T2>
auto add(T1 const &t1, T2 const &t2) -> decltype(T1 {} + T2 {}) {
    return t1 + t2;
}

TEST(对模板参数推导的更多介绍, C) {
}

const std::string message { "Test" };

std::string const &getString() {
    return message;
}

TEST(对模板参数推导的更多介绍, auto和decltype) {
    auto s1 { getString() };
    const auto &s2 { getString() };
    decltype(getString()) s3 { getString() };
    decltype(auto) s4 { getString() };
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

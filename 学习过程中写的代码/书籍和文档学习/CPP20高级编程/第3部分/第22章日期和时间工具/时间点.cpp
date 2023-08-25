#include <bits/chrono.h>
#include <chrono>
#include <iostream>
#include <gtest/gtest.h>

// time_point

TEST(时间点, time_point) {
    std::chrono::time_point<std::chrono::steady_clock> tp1;
    tp1 += std::chrono::minutes { 10 };
    auto d1 { tp1.time_since_epoch() };
    std::chrono::duration<double> d2 { d1 };
    std::cout << d2.count() << " seconds" << std::endl;

    using namespace std;

    std::chrono::time_point<std::chrono::steady_clock, std::chrono::seconds> tpSeconds { 42s };
    chrono::time_point<chrono::steady_clock, chrono::milliseconds> tpMilliseconds { tpSeconds };
    std::cout << tpMilliseconds.time_since_epoch().count() << "ms" << std::endl;

    chrono::time_point<chrono::steady_clock, chrono::milliseconds> tpMillseconds { 42'424ms };
    chrono::time_point<chrono::steady_clock, chrono::seconds> tpSeconds1 {
        chrono::time_point_cast<chrono::seconds>(tpMillseconds)
    };
    chrono::milliseconds ms { tpSeconds1.time_since_epoch() };
    std::cout << ms.count() << " ms" << std::endl;
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

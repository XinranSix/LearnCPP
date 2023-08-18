#include <bits/chrono.h>
#include <chrono>
#include <iostream>
#include <gtest/gtest.h>
#include <ratio>

TEST(持续时间, duration) {
    // std::chrono::duration<long> d1;
    std::chrono::duration<long, std::ratio<1>> d1;
    std::chrono::duration<long, std::ratio<60>> d2;
    std::chrono::duration<long, std::ratio<1, 60>> d3;
    std::chrono::duration<long, std::milli> d4;
}

TEST(持续时间, duration的应用) {
    std::chrono::duration<long, std::ratio<60>> d1 { 123 };
    std::cout << d1.count() << std::endl;

    auto d2 { std::chrono::duration<double>::max() };
    std::cout << d2.count() << std::endl;

    std::chrono::duration<long, std::ratio<60>> d3 { 10 };
    std::chrono::duration<long, std::ratio<1>> d4 { 14 };

    if (d3 > d4) {
        std::cout << "d3 > d4" << std::endl;
    } else {
        std::cout << "d3 <= d4" << std::endl;
    }

    ++d4;

    d4 * 2;

    std::chrono::duration<double, std::ratio<60>> d5 { d3 + d4 };
    std::chrono::duration<double, std::ratio<1>> d6 { d3 + d4 };

    std::cout << std::format("{} minutes + {} seconds = {} minutes or {} seconds", d3.count(),
                             d4.count(), d5.count(), d6.count())
              << std::endl;

    std::chrono::duration<long> d7 { 30 };

    std::chrono::duration<double, std::ratio<60>> d8 { d7 }; // Error
    // std::chrono::duration<long, std::ratio<60>> d9 { d7 };   // Error
    auto d10 { std::chrono::duration_cast<std::chrono::duration<long, std::ratio<60>>>(d7) };
    std::cout << std::format("{} seconds = {} minutes", d7.count(), d8.count()) << std::endl;

    auto t { std::chrono::hours { 1 } + std::chrono::minutes { 23 } + std::chrono::seconds { 45 } };
    std::cout << std::format("{} seconds", std::chrono::seconds { t }.count()) << std::endl;
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

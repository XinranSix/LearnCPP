#include <iostream>
#include <gtest/gtest.h>
#include <thread>
#include <vector>
#include <latch>

TEST(latch, C) {
    std::latch startLatch { 1 };
    std::vector<std::jthread> threads;
    for (int i { 0 }; i < 10; ++i) {
        threads.push_back(std::jthread { [&startLatch] { startLatch.wait(); } });
    }

    startLatch.count_down();
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

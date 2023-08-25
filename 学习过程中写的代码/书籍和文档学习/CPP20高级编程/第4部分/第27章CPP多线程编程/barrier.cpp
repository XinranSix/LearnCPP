#include <cstddef>
#include <iostream>
#include <gtest/gtest.h>
#include <barrier>

void completionFunction() noexcept {}

TEST(barrier, C) {
    // const size_t numberOfThreads { 4 };
    // barrier barrierPoint{numberOfThreads};
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

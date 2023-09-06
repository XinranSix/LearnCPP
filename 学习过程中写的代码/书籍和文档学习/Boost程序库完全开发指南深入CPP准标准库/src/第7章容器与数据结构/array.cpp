#include <iostream>
#include <gtest/gtest.h>
#include "boost/array.hpp"

// NOTE: 用什么 boost::array, std::array 不香嘛

TEST(array, C) {}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

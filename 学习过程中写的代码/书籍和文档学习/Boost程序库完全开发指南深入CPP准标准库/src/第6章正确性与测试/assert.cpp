#include <iostream>
#include <gtest/gtest.h>
#include <string>
#include "boost/assert.hpp"

double func(int x) {
    BOOST_ASSERT_MSG(x != 0, "divided by zero");
    return 1.0 / x;
}

TEST(assert, 基本用法) {
    BOOST_ASSERT(16 == 0x10);
    BOOST_ASSERT(std::string {}.size() == 1);

    // func(0); // Error
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

#include <iostream>
#include <gtest/gtest.h>
#include "boost/static_assert.hpp"

TEST(static_assert, 用法) {
    BOOST_STATIC_ASSERT(2 == sizeof(short));
    BOOST_STATIC_ASSERT(true);
    BOOST_STATIC_ASSERT_MSG(16 == 0x10, "test static assert");
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

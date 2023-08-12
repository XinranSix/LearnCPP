#include <iostream>
#include <gtest/gtest.h>

template <typename T>
constexpr T pi { T { 3.141592653589 } };

TEST(变量模板, C) {
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

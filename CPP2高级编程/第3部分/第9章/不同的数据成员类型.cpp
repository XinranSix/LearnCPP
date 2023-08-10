#include "professional_cpp/spreadsheet.hpp"
#include <iostream>
#include <gtest/gtest.h>

TEST(不同的数据成员, 静态数据成员) {
}

TEST(不同的数据成员, 引用数据成员) {
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

#include <iostream>
#include <gtest/gtest.h>

// 你在说什么？
TEST(数组和指针的对偶性, 数组就是指针) {
    int myIntArray[10]{};
    int *myIntPtr{myIntArray};
    myIntPtr[4] = 5;
}



int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


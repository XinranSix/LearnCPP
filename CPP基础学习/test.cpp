#include <iostream>
#include <gtest/gtest.h>

TEST(test, 异或交换两数) {
    int a = 1;
    int b = 1;

    std::cout << a << ' ' << b << std::endl;
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;
    std::cout << a << ' ' << b << std::endl;
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

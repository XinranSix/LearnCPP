#include <iostream>
#include <gtest/gtest.h>

void f1() noexcept {}
void f2() noexcept(false) {}
void f3() noexcept(noexcept(f1())) {}
void f4() noexcept(noexcept(f2())) {}

TEST(noexcept, 作为说明符) {}

TEST(noexcept, 作为运算符) {
    std::cout << noexcept(f1()) << noexcept(f2()) << noexcept(f3())
              << noexcept(f4()) << std::endl;
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

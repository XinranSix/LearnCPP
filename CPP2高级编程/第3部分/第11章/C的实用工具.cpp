#include <iostream>
#include <gtest/gtest.h>
#include <cstdio>
#include <cstdlib>
#include <cstdarg>

bool debug { true };

void debugOut(const char *str, ...) {
    va_list ap;
    if (debug) {
        va_start(ap, str);
        vfprintf(stderr, str, ap);
        va_end(ap);
    }
}

TEST(C的实用工具, 变参数列表) {
    printf("int %d\n", 5);
    printf("String %s and int %d \n", "hello", 5);
    printf("Many int: %d, %d, %d, %d, %d", 1, 2, 3, 4, 5);

    debugOut("int %d\n", 5);
    debugOut("String %s and int %d\n", "hello", 5);
    debugOut("Many int: %d, %d, %d, %d, %d\n", 1, 2, 3, 4, 5);
}

void printInts(size_t num, ...) {
    va_list ap;
    va_start(ap, num);
    for (size_t i { 0 }; i < num; ++i) {
        int temp { va_arg(ap, int) };
        std::cout << temp << ' ';
    }
    va_end(ap);
    std::cout << std::endl;
}

TEST(C的实用工具, vaarg) {
    printInts(5, 5, 4, 3, 2, 1);
}

#define SQUARE(x) ((x) * (x))

TEST(C的实用工具, 预处理器宏) {
    std::cout << SQUARE(5) << std::endl;
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

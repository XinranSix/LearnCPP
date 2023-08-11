#include <iostream>
#include <gtest/gtest.h>

wchar_t *toCaps(const wchar_t *text) { return nullptr; }

TEST(底层内存操作, 指针运算) {
    int *myArray{new int[8]};
    myArray[2] = 33;
    *(myArray + 2) = 33;

    const wchar_t *myString{L"Hello, World"};
    toCaps(myString + 7);
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

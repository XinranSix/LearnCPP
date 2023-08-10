#include <format>
#include <iostream>
#include <gtest/gtest.h>
#include <type_traits>

// 你在说什么？
TEST(数组和指针的对偶性, 数组就是指针) {
    int myIntArray[10]{};
    int *myIntPtr{myIntArray};
    myIntPtr[4] = 5;
}

void doubleInts(int *theArray, size_t size) {
    for (size_t i{0}; i < size; ++i) {
        theArray[i] *= 2;
    }
}

TEST(数组和指针的对偶性, 数组作为参数的几种情况) {

    size_t arrSize{4};
    int *freeStoreArray{new int[arrSize]{1, 5, 3, 4}};
    doubleInts(freeStoreArray, arrSize);
    delete[] freeStoreArray;
    freeStoreArray = nullptr;

    int stackArray[]{5, 7, 9, 11};
    arrSize = std::size(stackArray);
    doubleInts(stackArray, arrSize);
    doubleInts(&stackArray[0], arrSize);
}

TEST(数组和指针的对偶性, 数组作为参数与指针之前的关系) {

    std::cout << std::format("{}", std::is_same_v<int[], int *>) << std::endl;
    std::cout << std::format("{}", std::is_same_v<int[], int *const>)
              << std::endl;
    std::cout << std::format("{}", std::is_same_v<std::decay_t<int[]>, int *>)
              << std::endl;
}

template<size_t N>
void doubleIntsStack(int (&theArray)[N]) {
    for (size_t i{0}; i < N; ++i) {
        theArray[i] *= 2;
    }
}

TEST(数组和指针的对偶性, 数组不是指针) { int *ptr{new int}; }

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

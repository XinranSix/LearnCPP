#include <iostream>
#include <gtest/gtest.h>

TEST(数组, 基本类型的数组) {
    int myArray[5];

    // int len = 10;
    // int arr[len]; // 非标准语法

    int myArray1[5]{1, 2, 3, 4, 5};
    int myArray2[5]{1, 2};
    int myArray3[5]{0};
    int myArray4[5]{};
    int myArray5[]{1, 2, 3, 4, 5};

    int *ptrArrayPtr{new int[5]};
    int *ptrArrayPtr1{new (std::nothrow) int[5]};
    int *ptrArrayPtr2{new int[]{1, 2, 3, 4, 5}};

    delete[] ptrArrayPtr;
    ptrArrayPtr = nullptr;
    delete[] ptrArrayPtr1;
    ptrArrayPtr1 = nullptr;
    delete[] ptrArrayPtr2;
    ptrArrayPtr2 = nullptr;
}

TEST(数组, 对象的数组) {

    struct Simple {
        Simple() { std::cout << "Simple constructor called!" << std::endl; }
        ~Simple() { std::cout << "Simple destructor called!" << std::endl; }
    };

    Simple *mySimpleArray{new Simple[4]};
    delete[] mySimpleArray;
    mySimpleArray = nullptr;
}

TEST(数组, 指针数组) {

    struct Simple {
        Simple() { std::cout << "Simple constructor called!" << std::endl; }
        ~Simple() { std::cout << "Simple destructor called!" << std::endl; }
    };

    const size_t size{4};
    Simple **mySimplePtrArray{new Simple *[size]};

    for (size_t i{0}; i < size; ++i) {
        mySimplePtrArray[i] = new Simple{};
    }

    for (size_t i{0}; i < size; ++i) {
        delete mySimplePtrArray[i];
        mySimplePtrArray[i] = nullptr;
    }

    delete[] mySimplePtrArray;
    mySimplePtrArray = nullptr;
}

TEST(数组, 多维数组) {
    char board[3][3]{};

    board[0][0] = 'X';
    board[2][1] = 'O';
}

char **allocateCharacterBoard(size_t xDimension, size_t yDimension) {
    char **myArray{new char *[xDimension]};
    for (size_t i{0}; i < xDimension; ++i) {
        myArray[i] = new char[yDimension];
    }
    return myArray;
}

void releaseCharacterBoard(char **&myArray, size_t xDimension) {
    for (size_t i{0}; i < xDimension; ++i) {
        delete[] myArray[i];
        myArray[i] = nullptr;
    }
    delete[] myArray;
    myArray = nullptr;
}

TEST(数组, 自由存储区的多维数组) {

    // int i{};
    // int j{};
    // char **board{new char[i][j]}; //Error
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

#include <iostream>
#include <gtest/gtest.h>

TEST(使用指针, 滥用) { char *scaryPointer{(char *)7}; }

struct Document {};
Document *getDocument() { return nullptr; };

TEST(使用指针, 指针类型转换) {
    Document *documentPtr{getDocument()};
    char *myCharPyr{(char *)documentPtr}; // 不推荐

    // Document *documentPtr1{getDocument()};
    // char *myCharPyr1{static_cast<char*>(documentPtr1)}; // Error
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

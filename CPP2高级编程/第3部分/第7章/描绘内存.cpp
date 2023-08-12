#include <iostream>
#include <gtest/gtest.h>
#include <new>

TEST(描绘内存, 各种存储区上的变量) {
    int i { 7 };
    int *ptr { new int };

    int **handle { nullptr };
    handle = new int *;
    *handle = new int;
}

void leaky() {
    new int;
    std::cout << "I just leak an int" << std::endl;
}

TEST(描绘内存, 分配和释放) {
    leaky();

    int *ptr { new int };
    delete ptr;
    ptr = nullptr;
    delete ptr;
}

TEST(描绘内存, malloc和free) {

    // malloc 不会调用构造子

    struct Foo {
        Foo() {
            std::cout << "默认构造子" << std::endl;
        }
    };

    Foo *myFoo { (Foo *)malloc(sizeof(Foo)) };
    Foo *myOtherFoo { new Foo() };
}

TEST(描绘内存, new失败时) {

    int *ptr { new (std::nothrow) int };
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

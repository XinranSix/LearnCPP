#include <iostream>
#include <gtest/gtest.h>

class Foo;

void printFoo(Foo const &) {}

class Bar {
public:
    void processFoo(Foo const &) {}
};

class Foo {
    // friend class Bar;
    friend void Bar::processFoo(Foo const &);
    friend void printFoo(Foo const &);
};

TEST(M, C) {}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

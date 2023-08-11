#include <iostream>
#include <gtest/gtest.h>

struct Base {};

struct Derived : Base {};

TEST(向下转型和向上转型, 向上转型) {
    Derived myDerived;
    Base myBase { myDerived };
    Base &baseRef { myDerived };
}



TEST(向下转型和向上转型, 向下转型) {
  
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

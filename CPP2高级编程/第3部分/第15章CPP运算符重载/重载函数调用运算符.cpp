#include <iostream>
#include <gtest/gtest.h>

class FunctionObject {
public:
    int operator()(int param);
    int doSquare(int param);
};

int FunctionObject::operator()(int param) {
    return doSquare(param);
}

int FunctionObject::doSquare(int param) {
    return param * param;
}

TEST(重载函数调用运算符, 调用仿函数) {
    int x { 3 }, xSquared {}, xSquaredAgain {};
    FunctionObject square;
    xSquared = square(x);
    xSquaredAgain = square.doSquare(x);
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

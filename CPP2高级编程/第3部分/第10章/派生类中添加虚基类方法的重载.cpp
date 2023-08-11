#include <iostream>

struct Base {
    virtual void someMethod() {
    }
};

struct Derived : Base {
    using Base::someMethod;
    virtual void someMethod(int i) {
    }
    virtual void someOtherMethod() {
    }
};

int main(int argc, char *argv[]) {

    return 0;
}

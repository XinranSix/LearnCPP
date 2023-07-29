#include <iostream>

struct X {
    void f() { std::cout << "6\n"; }
    void f(int) { std::cout << "int\n"; }
};

void f2(void (X::*p)(), X *x, int n) { (x->*p)(); }

int main(int arvc, char *argv[]) {

    X x;
    f2(&X::f, &x, 6);

    return 0;
}

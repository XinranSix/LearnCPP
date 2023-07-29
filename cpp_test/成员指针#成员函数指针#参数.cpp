#include <iostream>

struct X {
    void f() { std::cout << "6\n"; }
};

void f2(void (X::*p)(), X &x) { (x.*p)(); }

int main(int arvc, char *argv[]) {

    X x;
    f2(&X::f, x);

    return 0;
}

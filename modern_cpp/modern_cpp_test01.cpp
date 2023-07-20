#include <iostream>

struct X {};

int main() {

    X x;

    X x2 = std::move(x);

    const X &x3 = std::move(x);

    return 0;
}

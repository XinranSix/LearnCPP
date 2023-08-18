#include <iostream>

struct X {
    int x = 1;
};

int main(int arvc, char *argv[]) {
    int X::*n = &X::x;

    X x;

    std::cout << x.*n << '\n';
    std::cout << x.x << '\n';

    int &v = x.*n;

    v = 100;
    std::cout << x.x << '\n';
    std::cout << x.*n << '\n';

    return 0;
}

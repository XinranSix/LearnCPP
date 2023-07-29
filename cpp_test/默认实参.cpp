#include <iostream>

void f(int, int, int = 3);

void f(int, int = 4, int);

void f(int = 5, int, int);

void f(int a, int b, int c) { std::cout << a << ' ' << b << ' ' << c << '\n'; }

int main(int arvc, char *argv[]) {
    f();
    return 0;
}

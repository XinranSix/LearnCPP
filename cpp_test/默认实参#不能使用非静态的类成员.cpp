#include <iostream>

struct X {
    int c = 6;
    static const int a = 6;
    void f(int n = sizeof c) { std::cout << n << '\n'; }
    void f_(int n = a) { std::cout << n << '\n'; }
};

int main(int arvc, char *argv[]) {
    X().f();
    X().f_();
    return 0;
}

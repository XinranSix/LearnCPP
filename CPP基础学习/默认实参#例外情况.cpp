#include <iostream>

template<class... T>
struct X {
    void f(int n = 0, T...) { std::cout << n << '\n'; }
};

template<class... Args>
void f_(int n = 6, Args... args) {
    std::cout << n << '\n';
}

void f() = delete;

int main(int arvc, char *argv[]) {
    X().f();
    X<int>().f(1, 2);

    // f_();
    // f_(1);
    // f_(1, 1.2);

    return 0;
}

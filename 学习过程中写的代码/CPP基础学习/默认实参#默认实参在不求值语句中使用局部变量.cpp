#include <iostream>

int main(int arvc, char *argv[]) {

    int f = 0;

    int i = 1;
    int j = 0;

    void f2(int n = sizeof f);
    // void f2(int n = i + j);

    f2();

    return 0;
}

void f2(int n) { std::cout << n << '\n'; }

// 默认实参中能在不求值语境使用局部变量，sizeof显然是不求值的，没有任何问题,但是msvc不行。
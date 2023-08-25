#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

int main(int argc, char *argv[]) {

    int a { 1 };

    decltype(a) b { 1 };

    return 0;
}

template <typename T>
void f() {
}

template <>
void f<int>() {
}

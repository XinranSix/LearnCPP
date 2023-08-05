#include <iostream>

template<typename T>
struct X {};

template<typename T>
struct Y {
    template<typename U>
    using type = X<U>;
};

template<typename T>
struct Z {
    template<typename U>
    using type = Y<U>;
};

int main(int arvc, char *argv[]) { return 0; }

#include <iostream>

template<typename T>
struct C {};

template<typename T>
struct B {
    template<typename T1>
    using type = C<T1>;
};

template<typename T>
struct A {
    template<typename T1>
    using type = B<T1>;
};

int main(int arvc, char *argv[]) {

    using F = A<int>::type<int>::type<int>;

    auto f = F{};

    return 0;
}

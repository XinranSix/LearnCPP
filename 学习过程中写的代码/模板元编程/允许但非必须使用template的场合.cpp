#include <iostream>

// 只要实际上是在一个成员模板 id 之前，在一个模板中的任何地方，template
// 关键字都是可选的。
template<typename T>
struct other {
    template<typename U>
    struct base;
};

template<typename T>
struct derived1 : other<int>::base<T> {};

template<typename T>
struct derived2 : other<int>::template base<T> {};

int main(int arvc, char *argv[]) { return 0; }

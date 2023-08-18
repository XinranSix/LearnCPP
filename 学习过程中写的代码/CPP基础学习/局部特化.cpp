#include <iostream>

template<typename T1, typename T2>
struct MyClass {};

template<typename T>
struct MyClass<T, T> {};

template<typename T>
struct MyClass<T, int> {};

template<typename T1, typename T2>
struct MyClass<T1 *, T2 *> {};

template<typename T>
struct MyClass<T *, T *> {};

template<>
struct MyClass<int, int> {};

int main(int arvc, char *argv[]) {

    MyClass<int, int> m;

    MyClass<int *, int *> m1;

    return 0;
}

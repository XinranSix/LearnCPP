#include <iostream>

// 使用 .、->、: 限定的依赖名访问成员模板之前，template 关键字必不可少
// convert 和 base 都依赖于 T
template<typename T>
void f(T &x, T *y) {
    int n = x.template convert<int>();
    int m = y->template convert<int>();
}

template<typename T>
struct other;

template<typename T>
struct derived : other<T>::template base<int> {};

int main(int arvc, char *argv[]) { return 0; }

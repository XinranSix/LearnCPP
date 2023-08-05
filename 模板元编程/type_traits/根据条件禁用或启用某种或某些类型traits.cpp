#include <iostream>
#include <type_traits>

template<typename T>
std::enable_if_t<std::is_arithmetic_v<T>, T> foo(T t) {
    std::cout << t << std::endl;
    return t;
}

template<typename T>
std::enable_if_t<!std::is_arithmetic_v<T>, int> foo(T t) {
    // std::cout << typeid(T).name << std::endl;
    return 1;
}

int main(int arvc, char *argv[]) {

    auto f = foo(1);
    auto r1 = foo(1.2);
    auto r2 = foo("hello");

    return 0;
}

#include <iostream>

template<typename T, typename = void>
struct has_type : std::false_type {};

template<typename T>
struct has_type<T, std::void_t<typename T::type>> : std::true_type {};

struct X {};

struct Y : X {};

int main(int arvc, char *argv[]) {

    std::cout << has_type<X>::value << std::endl;
    std::cout << has_type<X>::value << std::endl;

    return 0;
}

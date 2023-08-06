#include <iostream>

template<typename T1, typename T2>
struct X {
    constexpr static bool value = false;
};

template<typename T>
struct X<T, T> {
    constexpr static bool value = true;
};

int main(int argc, char *argv[]) {

    std::cout << X<int, int>::value << std::endl;                 // 1
    std::cout << X<int, double>::value << std::endl;              // 0
    std::cout << X<const int &, int const &>::value << std::endl; // 1
    std::cout << X<const int *, int const *>::value << std::endl; // 1
    std::cout << X<int *const, int const *>::value << std::endl;  // 0

    return 0;
}

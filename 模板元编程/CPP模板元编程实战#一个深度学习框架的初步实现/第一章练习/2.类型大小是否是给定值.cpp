#include <iostream>

template<typename T, size_t size>
struct X_ {
    constexpr static bool value = sizeof(T) == size;
};

template<typename T, size_t size>
constexpr static bool X = X_<T, size>::value;

int main(int arvc, char *argv[]) {

    std::cout << X<int, 4> << std::endl;
    std::cout << X<int *, 8> << std::endl;
    std::cout << X<int &, 4> << std::endl;

    return 0;
}

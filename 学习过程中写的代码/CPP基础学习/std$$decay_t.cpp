#include <ios>
#include <iostream>
#include <type_traits>

int main() {
    using T1 = int;
    using T2 = int &;
    using T3 = const int;
    using T4 = int[5];

    std::cout << std::boolalpha
              << std::is_same_v<std::decay_t<T1>, int> << std::endl; // true
    std::cout << std::boolalpha
              << std::is_same_v<std::decay_t<T2>, int> << std::endl; // true
    std::cout << std::boolalpha
              << std::is_same_v<std::decay_t<T3>, int> << std::endl; // true
    std::cout << std::boolalpha
              << std::is_same_v<std::decay_t<T4>, int *> << std::endl; // true
}

#include <ios>
#include <iostream>

template<typename T>
struct add_const_ref {
    using type = T const &;
};

template<typename T>
struct add_const_ref<T &> {
    using type = T &;
};

template<typename T>
struct add_const_ref<T &&> {
    using type = T &&;
};

int main(int arvc, char *argv[]) {

    int a = 0;
    int &lref = a;
    int &&rref = std::move(a);

    std::cout << std::boolalpha
              << std::is_same<int const &, add_const_ref<int>::type>::value
              << std::endl;

    std::cout << std::boolalpha
              << std::is_same<int &, add_const_ref<int &>::type>::value
              << std::endl;

    std::cout << std::boolalpha
              << std::is_same<int &&, add_const_ref<int &&>::type>::value
              << std::endl;

    return 0;
}

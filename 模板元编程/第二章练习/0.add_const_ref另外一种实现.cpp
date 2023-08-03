#include <iostream>
#include <type_traits>

template<bool, typename T>
struct add_const_reference;

template<typename T>
struct add_const_ref {
    using type = add_const_reference<std::is_reference<T>::value, T>::type;
};

template<typename T>
struct add_const_reference<false, T> {
    using type =
        std::add_lvalue_reference<typename std::add_const<T>::type>::type;
};

template<typename T>
struct add_const_reference<true, T> {
    using type = T;
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

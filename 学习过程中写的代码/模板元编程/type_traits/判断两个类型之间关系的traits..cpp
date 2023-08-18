#include <ios>
#include <iostream>
#include <type_traits>

struct A {};

struct B : A {};

struct C {};

int main(int arvc, char *argv[]) {

    std::cout << std::boolalpha << std::is_same_v<int, int> << std::endl;
    std::cout << std::boolalpha << std::is_same_v<int, float> << std::endl;

    std::cout << std::boolalpha << std::is_base_of_v<A, B> << std::endl;
    std::cout << std::boolalpha << std::is_base_of_v<A, C> << std::endl;

    std::cout << std::boolalpha << std::is_convertible_v<A, B> << std::endl;
    std::cout << std::boolalpha << std::is_convertible_v<A, C> << std::endl;
    std::cout << std::boolalpha << std::is_convertible_v<int, char> << std::endl;

    return 0;
}

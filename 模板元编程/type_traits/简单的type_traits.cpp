#include <iostream>
#include <type_traits>

template<typename T>
struct GetLeftSize : std::integral_constant<int, 1> {};

int main(int arvc, char *argv[]) {

    std::cout << GetLeftSize<int>::value << std::endl;

    return 0;
}

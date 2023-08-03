#include <iostream>

template<typename T>
struct size_of_type {
    constexpr static size_t value = sizeof(T);
};

int main(int arvc, char *argv[]) {

    std::cout << size_of_type<char>::value << std::endl;
    std::cout << size_of_type<int>::value << std::endl;
    std::cout << size_of_type<float>::value << std::endl;
    std::cout << size_of_type<double>::value << std::endl;

    return 0;
}

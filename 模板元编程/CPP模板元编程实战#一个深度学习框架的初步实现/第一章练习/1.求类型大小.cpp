#include <iostream>
#include <type_traits>

template<typename T>
struct SizeOfType_ {
    constexpr static size_t value = sizeof(T);
};

template<typename T>
constexpr static size_t SizeOfType = SizeOfType_<T>::value;

int main(int arvc, char *argv[]) {

    std::cout << SizeOfType<int> << std::endl;
    std::cout << SizeOfType<int &> << std::endl;
    std::cout << SizeOfType<int *> << std::endl;
    std::cout << SizeOfType<int **> << std::endl;
    std::cout << SizeOfType<int ***> << std::endl;
    std::cout << SizeOfType<int ***> << std::endl;

    return 0;
}

#include <cstddef>
#include <iostream>

template<size_t size, typename T>
struct is_equal_size {
    constexpr static bool value = size == sizeof(T);
};

int main(int arvc, char *argv[]) {

    std::cout << is_equal_size<4, int>::value << std::endl;
    std::cout << is_equal_size<5, int>::value << std::endl;

    return 0;
}

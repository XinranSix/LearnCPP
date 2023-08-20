#include <iostream>

template <size_t N>
struct fibonacci {
    static const unsigned long long value = fibonacci<N - 1>::value + fibonacci<N - 2>::value;
};

template <>
struct fibonacci<1> {
    static const unsigned long long value = 1ULL;
};

template <>
struct fibonacci<0> {
    static const unsigned long long value = 0ULL;
};

template <size_t N>
constexpr unsigned long long fibonacci_v = fibonacci<N>::value;

int main(int argc, char *argv[]) {

    std::cout << fibonacci_v<0> << std::endl;
    std::cout << fibonacci_v<1> << std::endl;
    std::cout << fibonacci_v<2> << std::endl;
    std::cout << fibonacci_v<3> << std::endl;
    std::cout << fibonacci_v<4> << std::endl;
    std::cout << fibonacci_v<5> << std::endl;
    std::cout << fibonacci_v<6> << std::endl;
    std::cout << fibonacci_v<7> << std::endl;
    std::cout << fibonacci_v<8> << std::endl;
    std::cout << fibonacci_v<9> << std::endl;
    std::cout << fibonacci_v<10> << std::endl;
    std::cout << fibonacci_v<11> << std::endl;
    std::cout << fibonacci_v<12> << std::endl;
    std::cout << fibonacci_v<13> << std::endl;
    std::cout << fibonacci_v<14> << std::endl;

    return 0;
}

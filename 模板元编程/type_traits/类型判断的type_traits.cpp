#include <ios>
#include <iostream>
#include <type_traits>

int main(int arvc, char *argv[]) {

    std::cout << std::boolalpha << std::is_integral_v<bool> << std::endl;
    std::cout << std::boolalpha << std::is_integral_v<char> << std::endl;
    std::cout << std::boolalpha << std::is_integral_v<char16_t> << std::endl;
    std::cout << std::boolalpha << std::is_integral_v<char32_t> << std::endl;
    std::cout << std::boolalpha << std::is_integral_v<short> << std::endl;
    std::cout << std::boolalpha << std::is_integral_v<long> << std::endl;
    std::cout << std::boolalpha << std::is_integral_v<long long> << std::endl;
    std::cout << std::boolalpha << std::is_integral_v<size_t> << std::endl;

    std::cout << std::boolalpha << std::is_void_v<void> << std::endl;
    std::cout << std::boolalpha << std::is_floating_point_v<float> << std::endl;
    std::cout << std::boolalpha << std::is_floating_point_v<double> << std::endl;

    std::cout << std::boolalpha << std::is_const_v<const int> << std::endl;

    return 0;
}

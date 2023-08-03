#include <cstddef>
#include <iostream>
#include "output_container.h"
#include <array>

template<typename... Args>
constexpr static std::array<size_t, sizeof...(Args)> sizeof_type = {};

template<typename First, typename... Others>
constexpr static std::array<size_t, sizeof...(Others) + 1>
    sizeof_type<First, Others...> = {sizeof(First), sizeof(Others)...};

template<typename... Args>
struct get_size_of_types {
    constexpr static std::array<size_t, sizeof...(Args)> value = {
        sizeof(Args)...};
};

int main(int arvc, char *argv[]) {

    std::cout << get_size_of_types<char, short, int, long, long long, float,
                                   double>::value
              << std::endl;

    std::cout << sizeof_type<char, short, int, long, long long, float,
                             double> << std::endl;

    return 0;
}

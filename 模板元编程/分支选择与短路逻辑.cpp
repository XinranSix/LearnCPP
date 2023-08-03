#include <ios>
#include <iostream>

template<bool cur, typename TNext>
constexpr static bool AndValue = false;

template<typename TNext>
constexpr static bool AndValue<true, TNext> = TNext::value;

template<size_t N>
constexpr bool is_odd = ((N % 2) == 1);

template<size_t N>
struct AllOdd_ {
    constexpr static bool is_cur_odd = is_odd<N>;
    constexpr static bool value = AndValue<is_cur_odd, AllOdd_<N - 1>>;
};

// template<size_t N>
// struct AllOdd_ {
//     constexpr static bool is_cur_odd = is_odd<N>;
//     constexpr static bool is_pre_odd = AllOdd_<N - 1>::value;
//     constexpr static bool value = is_cur_odd && is_pre_odd;
// };

// template<>
// struct AllOdd_<0> {
//     constexpr static bool value = is_odd<0>;
// };

int main(int arvc, char *argv[]) {

    std::cout << std::boolalpha << AllOdd_<100>::value << std::endl;

    return 0;
}

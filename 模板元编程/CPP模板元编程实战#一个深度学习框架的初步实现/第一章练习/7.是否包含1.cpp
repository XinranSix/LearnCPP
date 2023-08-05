#include <cstddef>
#include <iostream>

template<size_t val>
constexpr static bool is_one = (val == 1);

template<bool cur, typename TNext>
constexpr static bool or_value = true;

template<typename TNext>
constexpr static bool or_value<false, TNext> = TNext::value;

template<size_t... Vals>
struct X_ {
    constexpr static bool value = false;
};

template<size_t First, size_t... Others>
struct X_<First, Others...> {
    constexpr static bool value = or_value<is_one<First>, X_<Others...>>;
};

template<size_t... Vals>
constexpr static bool X = X_<Vals...>::value;

int main(int arvc, char *argv[]) {

    std::cout << X<1, 2, 3, 5> << std::endl;
    std::cout << X<2, 3, 5> << std::endl;
    std::cout << X<2, 3, 1, 5> << std::endl;
    std::cout << X<> << std::endl;

    return 0;
}

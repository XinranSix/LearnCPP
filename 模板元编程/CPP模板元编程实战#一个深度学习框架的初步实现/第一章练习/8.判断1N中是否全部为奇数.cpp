#include <cstddef>
#include <iostream>

template<size_t N>
constexpr static bool is_odd = (N % 2) == 1;

template<bool cur, typename TNext>
constexpr static bool and_value = false;

template<typename TNext>
constexpr static bool and_value<true, TNext> = TNext::value;

template<size_t N>
struct X_ {
    constexpr static bool value = and_value<is_odd<N>, X_<N - 1>>;
};

template<>
struct X_<0> {
    constexpr static bool value = is_odd<0>;
};

int main(int arvc, char *argv[]) { return 0; }

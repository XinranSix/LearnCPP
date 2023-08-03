#include <cstddef>
#include <iostream>
#include <type_traits>
#include <utility>

template<size_t V>
constexpr bool is_zero = (V == 0);

template<bool cur, typename TNext>
constexpr static bool AndValue = false;

template<typename TNext>
constexpr static bool AndValue<true, TNext> = TNext::value;

template<typename T>
struct has_one {
    constexpr static bool value = false;
};

template<size_t V>
struct has_one<std::index_sequence<V>> {
    constexpr static bool value = is_zero<V>;
};

template<size_t V, size_t... Ns>
struct has_one<std::index_sequence<V, Ns...>> {
    constexpr static bool cur_is_zero = is_zero<V>;
    constexpr static bool value =
        AndValue<cur_is_zero, has_one<std::index_sequence<Ns...>>>;
};

int main(int arvc, char *argv[]) { return 0; }

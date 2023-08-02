#include <iostream>
#include <type_traits>

template<bool AddOrRemoveRef>
struct Fun_;

template<>
struct Fun_<true> {
    template<typename T>
    using type = std::add_lvalue_reference<T>;
};

template<>
struct Fun_<false> {
    template<typename T>
    using type = std::remove_reference<T>;
};

template<typename T>
template<bool AddOrRemove>
using Fun = typename Fun_<AddOrRemove>::template type<T>;

// template<bool AddOrRemove, typename T>
// using Fun = typename Fun_<AddOrRemove>::template type<T>;

// template<typename T>
// using Res_ = Fun<false, T>;

// Res_<int &>::type h = 3;

int main(int arvc, char *argv[]) { return 0; }

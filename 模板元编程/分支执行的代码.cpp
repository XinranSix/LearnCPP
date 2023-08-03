#include <iostream>

struct A;
struct B;

template<typename T>
struct Fun_ {
    constexpr static size_t value = 0;
};

template<>
struct Fun_<A> {
    constexpr static size_t value = 1;
};

template<>
struct Fun_<B> {
    constexpr static size_t value = 2;
};

template<typename T>
constexpr size_t Fun = 0;

template<>
constexpr size_t Fun<A> = 1;

template<>
constexpr size_t Fun<B> = 2;

int main(int arvc, char *argv[]) {

    constexpr size_t h = Fun_<B>::value;
    constexpr size_t h1 = Fun<B>;

    std::cout << h << std::endl;
    std::cout << h1 << std::endl;

    return 0;
}

// Error: 非完全特化的模板不能有完全特化的模板
// template<typename TW>
// struct Wrapper {
//     template<typename T>
//     struct Fun_ {
//         constexpr static size_t value = 0;
//     };

//     template<>
//     struct Fun_<int> {
//         constexpr static size_t value = 1;
//     };
// };

template<typename TW>
struct Wrapper {
    template<typename T, typename TDummy = void>
    struct Fun_ {
        constexpr static size_t value = 0;
    };

    template<typename TDummy>
    struct Fun_<int, TDummy> {
        constexpr static size_t value = 1;
    };
};

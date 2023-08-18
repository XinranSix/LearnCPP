#include <cstddef>
#include <iostream>

/*
C 和 X 完全不同，不替换
例如：
<int, long, Y> -> int
*/
template<typename C, typename X, typename Y>
struct _replace_type {
    using type = C;
};

/*
C 和 X 完全相同，直接替换成 Y 就好
例如：
<int, int, Y> -> Y
*/
template<typename X, typename Y>
struct _replace_type<X, X, Y> {
    using type = Y;
};

/*
X 和 Y 完全相同，无需替换
例如：<int, X, X> -> int
*/
template<typename C, typename X>
struct _replace_type<C, X, X> {
    using type = C;
};

// 递归入口
template<typename C, typename X, typename Y>
struct replace_type {
    using type = _replace_type<C, X, Y>::type;
};

/*
匹配指针
例如：
<int*, X, Y> -> <>
*/
template<typename NC, typename X, typename Y>
struct replace_type<NC *, X, Y> {
    using type = replace_type<NC, X, Y>::type *;
};

template<typename NC, typename X, typename Y, size_t size>
struct replace_type<NC[size], X, Y> {
    using type = replace_type<NC, X, Y>::type[size];
};

template<typename NC, typename X, typename Y>
struct replace_type<NC &, X, Y> {
    using type = replace_type<NC, X, Y>::type &;
};

template<typename NC, typename X, typename Y>
struct replace_type<NC &&, X, Y> {
    using type = replace_type<NC, X, Y>::type &&;
};
/* -------------------------------------------------------------------------- */
template<typename NC, typename X, typename Y>
struct replace_type<const NC, X, Y> {
    using type = const replace_type<NC, X, Y>::type;
};

template<typename NC, typename X, typename Y>
struct replace_type<volatile NC, X, Y> {
    using type = volatile replace_type<NC, X, Y>::type;
};
/* -------------------------------------------------------------------------- */
template<typename NC, typename NX, typename Y>
struct replace_type<NC *, NX *, Y> {
    using type = replace_type<NC, NX, Y>::type;
};

template<typename NC, typename NX, typename Y, size_t size>
struct replace_type<NC[size], NX[size], Y> {
    using type = replace_type<NC, NX, Y>::type;
};

template<typename NC, typename NX, typename Y>
struct replace_type<NC &, NX &, Y> {
    using type = replace_type<NC, NX, Y>::type;
};

template<typename NC, typename NX, typename Y>
struct replace_type<NC &&, NX &&, Y> {
    using type = replace_type<NC, NX, Y>::type;
};

template<typename NC, typename NX, typename Y>
struct replace_type<const NC, const NX, Y> {
    using type = replace_type<NC, NX, Y>::type;
};

template<typename NC, typename NX, typename Y>
struct replace_type<volatile NC, volatile NX, Y> {
    using type = replace_type<NC, NX, Y>::type;
};

template<typename NC, typename NX, typename Y>
struct replace_type<volatile const NC, volatile NX, Y> {
    using type = const replace_type<NC, NX, Y>::type;
};

template<typename NC, typename NX, typename Y>
struct replace_type<volatile const NC, const NX, Y> {
    using type = volatile replace_type<NC, NX, Y>::type;
};

template<typename NC, typename NX, typename Y>
struct replace_type<volatile const NC, volatile const NX, Y> {
    using type = replace_type<NC, NX, Y>::type;
};
/* -------------------------------------------------------------------------- */
template<typename X, typename Y, typename NCR>
struct replace_type<NCR(), X, Y> {
    using type = replace_type<NCR, X, Y>::type;
};

template<typename X, typename Y, typename NCR, typename NC1>
struct replace_type<NCR(NC1), X, Y> {
    using type = typename replace_type<NCR, X, Y>::type(
        typename replace_type<NC1, X, Y>::type);
};

template<typename X, typename Y, typename NCR, typename NC1, typename NC2>
struct replace_type<NCR(NC1, NC2), X, Y> {
    using type = typename replace_type<NCR, X, Y>::type(
        typename replace_type<NC1, X, Y>::type,
        typename replace_type<NC2, X, Y>::type);
};

// template<typename X, typename Y, typename NC1, typename... ts>
// struct replace_type<NC1 (*)(ts... q), X, Y> {
//     static constexpr size_t ss = sizeof...(ts);
//     using type = typename replace_type<NC1, X, Y>::type (*)(ts... q);
// };

int main(int arvc, char *argv[]) {

    std::cout
        << std::boolalpha
        << std::is_same<int *, replace_type<void *, void, int>::type>::value
        << std::endl;

    std::cout
        << std::boolalpha
        << std::is_same<long *[10], replace_type<int const *[10], int const,
                                                 long>::type>::value
        << std::endl;

    std::cout << std::boolalpha
              << std::is_same<long &(*)(long &),
                              replace_type<char &(*)(char &), char &,
                                           long &>::type>::value
              << std::endl;

    using t = replace_type<char &(*)(char &), char &, long &>::type;

    return 0;
}

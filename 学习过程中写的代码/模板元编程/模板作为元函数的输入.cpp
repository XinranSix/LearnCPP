#include <iostream>
#include <type_traits>

template<template<typename> class T1, typename T2>
struct Fun_ {
    using type = typename T1<T2>::type;
};

template<template<typename> class T1, typename T2>
using Fun = typename Fun_<T1, T2>::type;

int main(int arvc, char *argv[]) {

    Fun<std::remove_reference, int &> h = 3;

    return 0;
}

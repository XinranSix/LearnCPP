#include <iostream>

constexpr int fun(int a) { return a + 1; }

// static int call_count = 3;
// constexpr int fun2(int a) { return a + (call_count++); }

template<typename T>
struct Fun_ {
    using type = T;
};

template<>
struct Fun_<int> {
    using type = unsigned int;
};

template<>
struct Fun_<long> {
    using type = unsigned long;
};

Fun_<int>::type h = 3;

template<typename T>
using Fun = typename Fun_<T>::type;

Fun<int> h1 = 3;


int main(int arvc, char *argv[]) { return 0; }

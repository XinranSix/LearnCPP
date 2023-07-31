inline int const &max(int const &a, int const &b) { return a < b ? b : a; }

template<typename T>
inline T const &max(T const &a, T const &b) {
    return a < b ? b : a;
}

template<typename T>
inline T const &max(T const &a, T const &b, T const &c) {
    return ::max(::max(a, b), c);
}

#include <iostream>

int main(int arvc, char *argv[]) {

    ::max(7, 24, 68);
    ::max(7.0, 42.0);
    ::max('a', 'b');
    ::max(7, 42);
    ::max<>(7, 42);
    ::max<double>(7, 42);
    ::max('a', 42.7);

    return 0;
}

#include <iostream>
#include <vector>
#include "tools.h"

template <typename T, typename... TS>
auto make_vector(T t, TS... ts) -> std::vector<T> {
    return { t, ts... };
}

template <typename T>
auto make_vector() -> std::vector<T> {
    return {};
}

template <typename T, size_t N>
auto to_vector(T (&arr)[N]) -> std::vector<T> {
    return std::vector<T> { arr, arr + N };
}

int main(int argc, char *argv[]) {
    int arr[] { 1, 2, 3, 4, 5 };
    auto ts = to_vector(arr);
    std::cout << ts;

    return 0;
}

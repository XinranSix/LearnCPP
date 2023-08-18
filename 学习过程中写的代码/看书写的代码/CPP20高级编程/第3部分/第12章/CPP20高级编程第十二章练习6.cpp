#include <iostream>
#include <optional>
#include <concepts>

using namespace std;

template <std::equality_comparable T>
std::optional<size_t> Find(T const &value, T const *arr, size_t size) {
    for (size_t i { 0 }; i < size; ++i) {
        if (arr[i] == value) {
            return i;
        }
    }
    return std::nullopt;
}

template <std::equality_comparable T, size_t N>
std::optional<size_t> Find(T const &value, const T (&arr)[N]) {
    return Find(value, arr, N);
}

int main(int argc, char *argv[]) {

    return 0;
}

#include <cstddef>
#include <iostream>
#include <optional>

template <typename T>
size_t Find(T const &value, T const *arr, size_t size) {
    for (size_t i { 0 }; i < size; ++i) {
        if (arr[i] == value) {
            return i;
        }
    }
    return -1;
}

template <typename T>
size_t Find(T *value, T *const *arr, size_t size) {
    for (size_t i { 0 }; i < size; ++i) {
        if (*arr[i] == *value) {
            return i;
        }
    }
    return -1;
}

int main(int argc, char *argv[]) {
    return 0;
}

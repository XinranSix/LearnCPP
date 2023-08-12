#include <iostream>
#include <gtest/gtest.h>
#include <optional>

static const size_t NOT_FOUND = static_cast<size_t>(-1);

template <typename T>
std::optional<size_t> Find(T const &value, T const *arr, size_t size) {
    for (size_t i { 0 }; i < size; ++i) {
        if (arr[i] == value) {
            return i;
        }
    }
    return std::nullopt;
}

template <typename T, size_t N>
std::optional<size_t> Find(T const &value, const T (&arr)[N]) {
    return Find(value, arr, N);
}

TEST(函数模板, 调用函数模板) {
    int myInt = 3, intArray[] = { 1, 2, 3, 4 };
    const size_t sizeIntArray = std::size(intArray);

    std::optional<size_t> res;
    res = Find(myInt, intArray, sizeIntArray);
    res = Find<int>(myInt, intArray, sizeIntArray);
    if (res != std::nullopt) {
        std::cout << res.value_or(0) << std::endl;
    } else {
        std::cout << "Not found" << std::endl;
    }

    double myDouble = 5.6, doubleArray[] = { 1.2, 3.4, 5.7, 7.5 };
    const size_t sizeDoubleArray = std::size(doubleArray);

    res = Find(myDouble, doubleArray, sizeDoubleArray);
    res = Find<double>(myDouble, doubleArray, sizeDoubleArray);
    if (res != std::nullopt) {
        std::cout << res.value_or(0) << std::endl;
    } else {
        std::cout << "Not found" << std::endl;
    }

    res = Find<double>(myInt, doubleArray, sizeDoubleArray);

    int myInt1 { 3 }, intArray1[] { 1, 2, 3, 4 };
    auto res1 { Find(myInt1, intArray1) };
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

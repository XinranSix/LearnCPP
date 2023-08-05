#include <iostream>
#include <array>
#include <format>
#include <vector>
#include <compare>
#include <utility>
#include <optional>
#include <initializer_list>



int main(int arvc, char *argv[]) {

    std::array arr{1, 2, 3, 4};

    for (int i : arr) {
        std::cout << i << std::endl;
    }

    for (std::array arr1{1, 2, 3, 4}; int i : arr1) {
        std::cout << i << std::endl;
    }

    return 0;
}

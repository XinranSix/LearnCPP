#include <iostream>
#include <array>
#include <format>

int main(int arvc, char *argv[]) {

    std::array<int, 3> arr{9, 8, 7};
    std::cout << std::format("Array size = {}", arr.size()) << std::endl;
    std::cout << std::format("2nd element = {}", arr[1]) << std::endl;

    std::array arr1{9, 7, 8};

    return 0;
}

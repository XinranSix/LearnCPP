#include <iostream>
#include <array>
#include <format>
#include <vector>
#include <compare>
#include <utility>
#include <optional>

int makeSum(std::initializer_list<int> values) {
    int total{0};
    for (int value : values) {
        total += value;
    }
    return total;
}

int main(int arvc, char *argv[]) {

    int a{makeSum({1, 2, 3})};
    int b{makeSum({10, 20, 30, 40, 50, 60})};

    return 0;
}

#include <algorithm>
#include <format>
#include <iostream>
#include <array>

int main(int argc, char *argv[]) {

    const size_t numberOfEmements{10};
    std::array<int, numberOfEmements> values;
    for (int index{0}; index < numberOfEmements; ++index) {
        values[index] = index;
    }
    values[values.size() - 1] = 99;

    std::for_each(values.begin(), values.end(),
                  [](int value) { std::cout << std::format("{} ", value); });

    return 0;
}

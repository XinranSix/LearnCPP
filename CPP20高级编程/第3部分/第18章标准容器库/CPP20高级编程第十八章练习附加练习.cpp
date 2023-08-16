#include <concepts>
#include <iostream>
#include <span>
#include <vector>
#include <array>

template <typename T>
    requires std::integral<T> || std::floating_point<T>
double average(std::span<const T> elements) {
    double res = 0;
    for (auto const &e : elements) {
        res += e;
    }
    return res / elements.size();
}

int main(int argc, char *argv[]) {

    std::vector values1 { 1.1, 2.2, 3.3, 4.4 };

    std::cout << average<double>(values1) << std::endl;

    std::array<int, 4> values2 { 1, 2, 3, 4 };
    std::cout << average<int>(values2) << std::endl;
    std::cout << average<int>({ values2.data() + 2, 2 }) << std::endl;

    return 0;
}

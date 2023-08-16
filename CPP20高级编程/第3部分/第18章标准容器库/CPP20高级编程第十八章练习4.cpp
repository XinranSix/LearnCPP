#include <iostream>
#include <span>
#include <vector>
#include <array>

double average(std::span<const double> elements) {
    double res = 0;
    for (auto const &e : elements) {
        res += e;
    }
    return res / elements.size();
}

int main(int argc, char *argv[]) {

    std::vector values1 { 1.1, 2.2, 3.3, 4.4 };
    std::cout << average(values1) << std::endl;

    std::array<double, 4> values2 { 1.1, 2.2, 3.3, 4.4 };
    std::cout << average(values2) << std::endl;
    std::cout << average({ values2.data() + 2, 2 }) << std::endl;

    return 0;
}

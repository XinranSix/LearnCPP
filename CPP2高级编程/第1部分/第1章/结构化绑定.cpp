#include <iostream>
#include <array>
#include <format>
#include <vector>
#include <compare>
#include <utility>
#include <optional>

struct Point {
    double m_x, m_y, m_z;
};

int main(int arvc, char *argv[]) {

    std::array values{11, 22, 33};
    auto [x, y, z]{values};

    Point point{1.0, 2.0, 3.0};

    auto [a, b, c]{point};

    std::pair myPair{"hello", 5};
    auto [theString, theInt]{myPair};
    std::cout << std::format("theSting: {}", theString) << std::endl;
    std::cout << std::format("theInt: {}", theInt) << std::endl;

    return 0;
}

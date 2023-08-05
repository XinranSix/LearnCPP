#include <iostream>
#include <array>
#include <format>
#include <vector>
#include <compare>
#include <utility>
#include <optional>

struct Demo {
    int get() { return 5; };
};

int get() { return 10; }

namespace yt {
    int get() { return 20; }
} // namespace yt

int main(int arvc, char *argv[]) {

    // using namespace yt;

    Demo d{};

    std::cout << d.get() << std::endl;   // 5
    std::cout << yt::get() << std::endl; // 20
    std::cout << ::get() << std::endl;   // 10
    std::cout << get() << std::endl;     // 10

    return 0;
}

#include <iostream>
#include <ranges>

int main(int argc, char *argv[]) {

    auto values { std::views::iota(10, 100) };

    auto result { values | std::views::transform([](auto const &v) { return v * v; }) |
                  std::views::drop_while([](auto const &v) { return v % 5 == 0; }) |
                  std::views::transform([](auto const &v) { return std::to_string(v); }) };

    for (auto const &v : result) {
        std::cout << v << ' ';
    }
    std::cout << std::endl;

    return 0;
}

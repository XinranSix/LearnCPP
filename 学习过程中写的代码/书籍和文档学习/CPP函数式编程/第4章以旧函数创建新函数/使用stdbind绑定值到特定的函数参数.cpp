#include "fmt/core.h"
#include <functional>
#include <iostream>

int main(int argc, char *argv[]) {

    auto bound { std::bind(std::greater<>(), 6, 42) };
    bool is_6_greater_than_42 { bound() };

    fmt::print("{}\n", is_6_greater_than_42);

    using namespace std::placeholders;

    auto is_greater_than_42 { std::bind(std::greater<>(), _1, 42) };
    auto is_less_than_42 { std::bind(std::greater<>(), 42, _1) };

    fmt::print("{}\n", is_less_than_42(6));
    fmt::print("{}\n", is_greater_than_42(6));

    return 0;
}

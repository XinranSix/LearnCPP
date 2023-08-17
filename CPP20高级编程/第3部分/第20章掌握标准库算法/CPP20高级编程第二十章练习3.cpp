#include <cctype>
#include <string>
#include <string_view>
#include <iostream>
#include <algorithm>
#include <format>

std::string trim(std::string_view text) {
    auto first { std::find_if(begin(text), cend(text), [](char c) { return !std::isspace(c); }) };
    auto last { std::find_if(rbegin(text), rend(text), [](char c) {
                    return !std::isspace(c);
                }).base() };
    return { first, last };
}

int main() {
    std::cout << std::format("'{}'\n", trim("   Hello World!   "));
    std::cout << std::format("'{}'\n", trim("Hello World!   "));
    std::cout << std::format("'{}'\n", trim("   Hello World!"));
    std::cout << std::format("'{}'\n", trim("Hello World!"));
    std::cout << std::format("'{}'\n", trim(" \t Hello World! \n"));

    return 0;
}

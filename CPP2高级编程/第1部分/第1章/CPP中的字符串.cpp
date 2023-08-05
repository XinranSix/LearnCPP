#include <iostream>
#include <array>
#include <format>
#include <vector>
#include <compare>
#include <utility>
#include <optional>
#include <string>

int main(int arvc, char *argv[]) {

    std::string myString{"hello world"};
    std::cout << std::format("The value of myString is {}", myString) << std::endl;
    std::cout << std::format("The second letter is {}", myString[1]) << std::endl;

    return 0;
}

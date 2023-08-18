#include <variant>
#include <iostream>
#include <string>

int main() {
    std::variant<int, double, std::string> myVariant;

    myVariant = 42;                                     // Store an int
    std::cout << std::get<int>(myVariant) << std::endl; // Access the stored int

    myVariant = 3.14; // Store a double
    std::cout << std::get<double>(myVariant)
              << std::endl; // Access the stored double

    myVariant = "Hello, Variant!"; // Store a string
    std::cout << std::get<std::string>(myVariant)
              << std::endl; // Access the stored string

    return 0;
}

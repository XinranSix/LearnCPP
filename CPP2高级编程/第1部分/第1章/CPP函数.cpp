#include <iostream>
#include <format>

auto addNumbers(int number1, int number2) {
    std::cout << std::format("Entering function {}", __func__) << std::endl;
    return number1 + number2;
}

int main(int arvc, char *argv[]) {
    addNumbers(1, 2);
    return 0;
}

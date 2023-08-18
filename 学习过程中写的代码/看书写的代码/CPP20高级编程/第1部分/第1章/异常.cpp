#include <format>
#include <iostream>
#include <stdexcept>

double divideNumbers(double numbertor, double denominator) {
    if (denominator == 0) {
        throw std::invalid_argument("Denominator cannot be 0.");
    }
    return numbertor / denominator;
}

int main(int arvc, char *argv[]) {

    try {
        std::cout << divideNumbers(2.5, 0.5) << std::endl;
        std::cout << divideNumbers(2.3, 0) << std::endl;
        std::cout << divideNumbers(4.5, 2.5) << std::endl;
    } catch (const std::invalid_argument &e) {
        std::cout << std::format("Exception caught: {}", e.what()) << std::endl;
    }

    return 0;
}

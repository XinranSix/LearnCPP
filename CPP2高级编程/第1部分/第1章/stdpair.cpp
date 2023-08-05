#include <iostream>
#include <utility>
#include <format>

int main(int arvc, char *argv[]) {

    std::pair<double, int> myPair{1.23, 5};

    std::cout << std::format("{} {}", myPair.first, myPair.second) << std::endl;

    std::pair myPair1{1.23, 5};

    return 0;
}

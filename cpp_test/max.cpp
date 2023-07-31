#include <iostream>
#include <string>
#include "basics/max.hpp"
#include <complex>

int main(int arvc, char *argv[]) {

    int i = 42;
    std::cout << "max(7, i): " << ::max(7, i) << std::endl;

    double f1 = 3.4;
    double f2 = -6.7;

    std::cout << "max(f1, f2): " << ::max(f1, f2) << std::endl;

    std::string s1 = "mathematics";
    std::string s2 = "math";
    std::cout << "max(s1, s2): " << ::max(s1, s2) << std::endl;

    ::max(4, 7);
    ::max(static_cast<double>(4), 4.2);
    ::max<double>(4, 4.2);

    ::max<int, double, double>(4, 4.2);
    ::max<double>(4, 4.2);

    return 0;
}

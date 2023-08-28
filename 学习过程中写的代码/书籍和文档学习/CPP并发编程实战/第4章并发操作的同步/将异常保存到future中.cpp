#include "fmt/core.h"
#include <cmath>
#include <exception>
#include <future>
#include <iostream>
#include <stdexcept>

double square_root(double x) {
    if (x < 0) {
        throw std::out_of_range { "x < 0" };
    }
    return std::sqrt(x);
}

int main(int argc, char *argv[]) {

    std::future<double> f = std::async(square_root, -1);
    try {
        double y = f.get();
        fmt::print("{}\n", y);
    } catch (std::exception e) {
        fmt::print("{}\n", e.what());
    }
    return 0;
}

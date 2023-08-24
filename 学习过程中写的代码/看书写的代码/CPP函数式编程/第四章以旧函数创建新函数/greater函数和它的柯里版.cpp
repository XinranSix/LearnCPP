#include "fmt/core.h"
#include <iostream>

// greater: (double, double) -> bool
bool greater(double first, double second) {
    return first > second;
}

// greater_curried: double -> (double -> bool)
auto greater_curried(double first) {
    return [first](double second) { return first > second; };
}

int main(int argc, char *argv[]) {

    fmt::print("{}\n", greater(2, 3));
    fmt::print("{}\n", greater_curried(2)(3));

    return 0;
}

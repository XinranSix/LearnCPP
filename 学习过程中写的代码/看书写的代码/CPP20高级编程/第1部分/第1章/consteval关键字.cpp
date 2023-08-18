#include <iostream>

constexpr double incgToMm(double inch) { return inch * 25.4; }
// consteval double incgToMm(double inch) { return inch * 25.4; }

int main(int arvc, char *argv[]) {

    constexpr double const_inch{6.0};
    constexpr double mml{incgToMm(const_inch)};

    double dynamic_inch{8.0};
    double mm2{incgToMm(dynamic_inch)};

    return 0;
}

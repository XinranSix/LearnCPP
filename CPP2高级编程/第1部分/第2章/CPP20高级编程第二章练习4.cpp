#include <iostream>
#include <vector>
#include <format>

int main(int argc, char *argv[]) {

    std::vector<float> fv;

    float f;
    std::cin >> f;
    while (f != 0) {
        fv.push_back(f);
        std::cin >> f;
    }

    for (auto value : fv) {
        std::cout << std::format("{0:16e} | {0:12f} | {0:<12g} | {0:#>+12g}",
                                 value)
                  << std::endl;
    }

    return 0;
}

#include <iostream>

enum class Mode { Default, Custom, Standard };

int main(int arvc, char *argv[]) {

    int value{42};
    Mode mode{Mode::Default};

    switch (mode) {
        using enum Mode;
    case Custom:
        value = 64;
        [[fallthrough]];
    case Standard:
    case Default:
        value = 32;
        break;
    }

    return 0;
}

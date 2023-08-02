#include <iostream>

struct always_int {
    using type = int;
};

int main(int arvc, char *argv[]) {

    always_int::type a = 1;

    return 0;
}

#include <iostream>

struct aggregate {
    // aggregate() = default;
    // aggregate(aggregate const &) = default;
    int a;
    double b;
};

int main(int arvc, char *argv[]) {

    aggregate x = {42, 3.141};

    return 0;
}

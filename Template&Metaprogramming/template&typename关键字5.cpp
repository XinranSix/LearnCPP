#include <iostream>

double const pi = 3.14159265359;

template<typename T>
int f(T &x) {
    return x.template convert<3>(pi);
}

int main(int arvc, char *argv[]) { return 0; }

#include <iostream>
#include <type_traits>

int main(int arvc, char *argv[]) {

    using T = std::conditional_t<true, int, double>;

    T a = 1;

    return 0;
}

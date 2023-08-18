#include <iostream>

template<typename T, int I>
class Mix;

using Int = int;

int main(int arvc, char *argv[]) {

    Mix<int, 3 * 3> *p1;
    Mix<int, 4 + 5> *p2;

    return 0;
}

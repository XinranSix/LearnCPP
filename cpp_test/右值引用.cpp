#include <iostream>
#include <cassert>

int main(int arvc, char *argv[]) {

    int var = 42;
    int &ref = var;
    ref = 99;
    assert(var == 99);

    int &&i = 42;
    int j = 42;
    int &&k = j;

    return 0;
}

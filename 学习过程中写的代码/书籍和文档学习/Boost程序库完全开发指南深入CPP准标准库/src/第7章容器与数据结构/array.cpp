#include <algorithm>
#include <cassert>
#include <iostream>
#include <ostream>
#include "boost/array.hpp"
#include "boost/assert.hpp"
#include "boost/signals2.hpp"

int main(int argc, char *argv[]) {

    boost::array<int, 10> ar;

    ar[0] = 1;
    ar.back() = 10;
    assert(ar[ar.max_size() - 1] == 10);

    ar.assign(777);
    for (auto x : ar) {
        std::cout << x << ", ";
    }
    std::endl(std::cout);

    int *p = ar.c_array();
    *(p + 5) = 253;
    std::cout << ar[5] << std::endl;

    ar.at(8) = 666;
    std::sort(ar.begin(), ar.end());
    for (auto x : ar) {
        std::cout << x << ", ";
    }
    std::endl(std::cout);

    return 0;
}

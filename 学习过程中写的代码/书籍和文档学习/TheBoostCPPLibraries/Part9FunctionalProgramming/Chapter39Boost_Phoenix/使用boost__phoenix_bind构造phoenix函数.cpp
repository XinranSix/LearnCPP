#include "fmt/core.h"
#include <algorithm>
#include <iostream>
#include <boost/phoenix/phoenix.hpp>
#include <vector>

bool is_odd(int i) {
    return i % 2 == 1;
}

int main(int argc, char *argv[]) {

    std::vector<int> v { 1, 2, 3, 4, 5 };

    using namespace boost::phoenix;
    using namespace boost::phoenix::placeholders;
    fmt::print("{}\n", std::count_if(cbegin(v), cend(v), bind(is_odd, arg1)));

    return 0;
}

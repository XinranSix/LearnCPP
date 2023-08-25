#include "fmt/core.h"
#include <algorithm>
#include <iostream>
#include <boost/phoenix/phoenix.hpp>
#include <vector>

int main(int argc, char *argv[]) {

    std::vector<int> v { 1, 2, 3, 4, 5 };

    using namespace boost::phoenix;
    using namespace boost::phoenix::placeholders;
    auto phoenix { arg1 > val(2) && arg1 % val(2) == val(1) };

    fmt::print("{}\n", std::count_if(cbegin(v), cend(v), phoenix));

    return 0;
}

#include "fmt/core.h"
#include <algorithm>
#include <bits/ranges_base.h>
#include <iostream>
#include <boost/phoenix/phoenix.hpp>
#include <vector>

int main(int argc, char *argv[]) {

    std::vector<int> v { 1, 2, 3, 4, 5 };

    using namespace boost::phoenix::placeholders;
    auto phoenix { arg1 > 2 && arg1 % 2 == 1 };
    fmt::print("{}\n", std::count_if(std::ranges::cbegin(v), cend(v), phoenix));

    return 0;
}

#include "fmt/core.h"
#include <iostream>
#include <boost/phoenix/phoenix.hpp>

int main(int argc, char *argv[]) {

    using namespace boost::phoenix::placeholders;
    fmt::print("{}\n", arg1(1, 2, 3, 4, 5));
    fmt::print("{}\n", arg2(1, 2, 3, 4, 5));

    auto v { boost::phoenix::val(2) };
    fmt::print("{}\n", v());

    return 0;
}

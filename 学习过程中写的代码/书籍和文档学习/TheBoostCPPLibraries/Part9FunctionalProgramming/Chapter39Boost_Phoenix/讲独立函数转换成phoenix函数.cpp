#include "boost/phoenix/function/adapt_function.hpp"
#include "fmt/core.h"
#include <algorithm>
#include <iostream>
#include <boost/phoenix/phoenix.hpp>
#include <vector>

// Pass the type of the return value, the name of the Phoenix function to define, the name of the
// free-standing function, and the number of parameters to the macro.
bool is_odd_function(int i) {
    return i % 2 == 1;
}

BOOST_PHOENIX_ADAPT_FUNCTION(bool, is_odd, is_odd_function, 1);

int main(int argc, char *argv[]) {

    std::vector<int> v { 1, 2, 3, 4, 5 };

    using namespace boost::phoenix::placeholders;
    fmt::print("{}\n", std::count_if(cbegin(v), cend(v), is_odd(arg1)));

    return 0;
}

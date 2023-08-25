#include "fmt/core.h"
#include <algorithm>
#include <boost/phoenix/phoenix.hpp>
#include <iostream>
#include <vector>

struct is_odd_impl {

    using result_type = bool;

    template <typename T>
    bool operator()(T t) const {
        return t % 2 == 1;
    }
};

boost::phoenix::function<is_odd_impl> is_odd;

int main(int argc, char *argv[]) {

    std::vector<int> v { 1, 2, 3, 4, 5 };

    using namespace boost::phoenix::placeholders;
    fmt::print("{}\n", std::count_if(cbegin(v), cend(v), is_odd(arg1)));

    return 0;
}

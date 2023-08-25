#include "fmt/core.h"
#include <algorithm>
#include <iostream>
#include <boost/phoenix/phoenix.hpp>
#include <vector>

int main(int argc, char *argv[]) {

    std::vector<int> v { 1, 2, 3, 4, 5 };

    using namespace boost::phoenix;
    using namespace boost::phoenix::placeholders;
    int count { 0 };
    std::for_each(cbegin(v), cend(v), if_(arg1 > 2 && arg1 % 2 == 1)[++ref(count)]);
    fmt::print("{}\n", count);

    return 0;
}

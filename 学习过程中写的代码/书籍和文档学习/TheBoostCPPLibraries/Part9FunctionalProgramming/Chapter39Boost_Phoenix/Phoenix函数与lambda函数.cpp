#include "fmt/core.h"
#include <algorithm>
#include <iostream>
#include <boost/phoenix/phoenix.hpp>

// phoenix function 参数是没有类型的
// lambda function 参数是有类型的
int main(int argc, char *argv[]) {

    std::vector<int> v { 1, 2, 3, 4, 5 };

    auto lambda { [](int i) { return i % 2 == 1; } };
    fmt::print("{}\n", std::count_if(cbegin(v), cend(v), lambda));

    std::vector<long> v2(v.size());
    v2.insert(begin(v2), begin(v), end(v));

    using namespace boost::phoenix::placeholders;
    auto phoenix { arg1 % 2 == 1 };
    fmt::print("{}\n", std::count_if(cbegin(v), cend(v), phoenix));
    fmt::print("{}\n", std::count_if(cbegin(v2), cend(v2), phoenix));
    // fmt::print("{}\n", std::count_if(cbegin(v2), cend(v2), lambda));//

    return 0;
}

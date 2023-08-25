#include "fmt/core.h"
#include <algorithm>
#include <iostream>
#include <boost/phoenix/phoenix.hpp>
#include <vector>

bool is_odd(int i) {
    return i % 2 == 1;
}

int main(int argc, char *argv[]) {

    std::vector<int> v { 1, 2, 3, 4, 5, 6 };

    // 全局函数
    fmt::print("{}\n", std::count_if(cbegin(v), cend(v), is_odd));

    // lambda 函数
    auto lambda { [](int i) { return i % 2 == 1; } };
    fmt::print("{}\n", std::count_if(cbegin(v), cend(v), lambda));

    // phoenix 函数phoenix
    using namespace boost::phoenix::placeholders;
    auto phoenix { arg1 % 2 == 1 };
    fmt::print("{}\n", std::count_if(cbegin(v), cend(v), phoenix));

    return 0;
}

#include <fmt/core.h>
#include <algorithm>
#include <iostream>
#include <boost/phoenix/phoenix.hpp>
#include <numeric>
#include <vector>

int main(int argc, char *argv[]) {

    using namespace boost::phoenix::placeholders;
    std::vector<int> numbers { 21, 5, 62, 42, 53 };
    std::partition(begin(numbers), end(numbers), arg1 <= 42);

    std::for_each(cbegin(numbers), cend(numbers), [](auto number) { fmt::print("{} ", number); });
    fmt::print("\n");

    auto sum { std::accumulate(cbegin(numbers), cend(numbers), 0, arg1 + arg2 * arg2 / 2) };
    fmt::print("{}\n", sum);

    auto product { std::accumulate(cbegin(numbers), cend(numbers), 1, arg1 * arg2) };
    fmt::print("{}\n", product);

    std::sort(begin(numbers), end(numbers), arg1 > arg2);
    std::for_each(cbegin(numbers), cend(numbers), [](auto number) { fmt::print("{} ", number); });
    fmt::print("\n");

    return 0;
}

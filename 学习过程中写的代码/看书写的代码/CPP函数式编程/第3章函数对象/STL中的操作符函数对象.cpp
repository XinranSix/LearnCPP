#include <algorithm>
#include <format>
#include <functional>
#include <iostream>
#include <iterator>
#include <numeric>
#include <string_view>
#include <vector>
#include <fmt/core.h>

int main(int argc, char *argv[]) {

    std::vector<int> numbers1 { 1, 2, 3, 4 };
    auto product { std::accumulate(cbegin(numbers1), cend(numbers1), 1, std::multiplies<int> {}) };

    fmt::print("{}\n", product);

    std::vector<int> numbers2 { 5, 21, 13, 42 };
    std::sort(begin(numbers2), end(numbers2), std::greater<> {});
    std::for_each(cbegin(numbers2), cend(numbers2), [](auto number) { fmt::print("{} ", number); });

    return 0;
}

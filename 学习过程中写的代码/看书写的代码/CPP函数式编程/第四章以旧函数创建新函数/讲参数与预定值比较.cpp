#include "fmt/core.h"
#include <algorithm>
#include <concepts>
#include <iostream>
#include <vector>

class greater_than {
public:
    greater_than(int value) : m_value { value } {}

    bool operator()(int arg) {
        return arg > m_value;
    }

private:
    int m_value;
};

int main(int argc, char *argv[]) {

    std::vector<int> xs { 274, 234, 745, 213, 356, 12, 4, 6, 1, 61, 356, 1, 34, 12 };

    greater_than greater_than_42 { 42 };

    fmt::print("{}\n", greater_than_42(1));
    fmt::print("{}\n", greater_than_42(50));

    std::partition(begin(xs), end(xs), greater_than { 6 });
    std::for_each(cbegin(xs), cend(xs), [](auto v) { fmt::print("{}", v); });

    return 0;
}

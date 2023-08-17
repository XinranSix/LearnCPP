#include <iostream>
#include <numeric>
#include <vector>
#include <deque>
#include "yj/yj.h"

int main(int argc, char *argv[]) {

    std::vector<int> values(100);
    std::iota(begin(values), end(values), 1);
    std::cout << values << std::endl;

    std::deque<int> evens, odds;
    std::partition_copy(begin(values), end(values), back_inserter(evens), front_inserter(odds),
                        [](int i) { return i % 2 == 0; });

    std::cout << "Even numbers: ";
    for (const auto &value : evens) {
        std::cout << value << " ";
    }
    std::cout << "\nOdd numbers: ";
    for (const auto &value : odds) {
        std::cout << value << " ";
    }

    return 0;
}

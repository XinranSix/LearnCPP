#include <algorithm>
#include <cstddef>
#include <iostream>
#include <vector>
#include "yj/yj.h"

int main(int argc, char *argv[]) {

    size_t number {};
    std::cin >> number;

    std::vector<int> values;
    int num {};
    while (number--) {
        std::cin >> num;
        values.push_back(num);
    }

    while (std::next_permutation(begin(values), end(values))) {
        std::cout << values << std::endl;
    }

    return 0;
}

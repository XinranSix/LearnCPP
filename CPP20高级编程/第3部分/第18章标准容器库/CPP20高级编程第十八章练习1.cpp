#include <iostream>
#include <vector>
#include "yj/tools/output_container.h"

int main(int argc, char *argv[]) {

    std::vector<int> values { 2, 5 };

    // 1
    values.insert(begin(values) + 1, 3);
    values.insert(begin(values) + 2, 4);

    // 2
    std::vector<int> v2 { 0, 1 };
    values.insert(begin(values), cbegin(v2), cend(v2));

    // 3
    std::vector<int> v3;
    for (auto riter { crbegin(values) }; riter != crend(values); ++riter) {
        v3.push_back(*riter);
    }

    // 4
    for (const auto &element : v3) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    return 0;
}

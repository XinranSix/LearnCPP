#include <algorithm>
#include <iostream>
#include <vector>
#include "yj/yj.h"

int main(int argc, char *argv[]) {

    std::vector<int> values(10);
    int num {};
    std::cin >> num;
    std::fill(begin(values), end(values), num);

    std::cout << values << std::endl;

    return 0;
}

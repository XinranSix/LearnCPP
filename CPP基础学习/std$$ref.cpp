#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

void add(int i, int j, std::ostream &os) {
    os << i + j << std::endl;
}

int main() {

    std::vector<int> v;
    v.push_back(1);
    v.push_back(3);
    v.push_back(2);

    std::for_each(
        v.begin(), v.end(),
        std::bind(add, 10, std::placeholders::_1, std::ref(std::cout)));

    return 0;
}
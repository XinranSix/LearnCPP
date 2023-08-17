#include <algorithm>
#include <iostream>
#include <functional>
#include <vector>

int main(int argc, char *argv[]) {

    std::vector<int> v { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 19, 10 };

    std::erase_if(v, [](int i) { return i % 2 == 1; });
    std::for_each(cbegin(v), cend(v), [](int i) { std::cout << i << ' '; });
    std::cout << std::endl;

    return 0;
}

int square(int value) { return value * value; }
int cube(int value) { return value * value * value; }

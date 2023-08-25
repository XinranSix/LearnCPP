#include <iostream>
#include <utility>
#include <vector>
#include <string>

template <typename T, typename... Args>
void push_back_values(std::vector<T> &v, Args &&...args) {
    (v.push_back(std::forward<Args>(args)), ...);
}

int main(int argc, char *argv[]) {

    std::vector<int> values1;
    push_back_values(values1, 9, 8, 7, 6);
    for (auto &value : values1) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    std::vector<double> values2;
    push_back_values(values2, 1.1, 2, 3.3, 4);
    for (auto &value : values2) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    std::vector<std::string> values3;
    push_back_values(values3, "Hello", "World", "!");
    for (auto &value : values3) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    return 0;
}

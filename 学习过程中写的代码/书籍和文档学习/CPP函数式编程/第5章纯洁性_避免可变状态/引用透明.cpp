#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>

double max(std::vector<double> const &numbers) {
    if (numbers.empty()) {
        throw std::runtime_error { "numbers is empty" };
    }
    auto result { std::max_element(cbegin(numbers), cend(numbers)) };
    // NOTE:此处去掉下面的打印代码，这个函数就是一个引用透明的函数，也是一个纯函数
    // std::cerr << "Maximum is: " << *result << std::endl;
    return *result;
}

int main(int argc, char *argv[]) {

    auto sum_max = max({ 1 }) + max({ 1, 2 }) + max({ 1, 2, 3 });

    std::cout << sum_max << std::endl;

    return 0;
}

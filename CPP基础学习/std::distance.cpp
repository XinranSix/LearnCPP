#include <iostream>
#include <iterator>
#include <vector>

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};

    // 使用 std::distance 计算两个迭代器之间的元素个数
    auto it1 = vec.begin();
    auto it2 = vec.end();
    std::ptrdiff_t distance = std::distance(it1, it2);

    std::cout << "Distance: " << distance << std::endl;

    return 0;
}

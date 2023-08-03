#include <iostream>
#include <functional>

void modifyValue(int &value) {
    value *= 2; // 修改原始对象
}

int main() {
    int num = 10;
    std::cout << "Original value: " << num << std::endl;

    // 使用 std::ref 将 num 封装为引用
    modifyValue(std::ref(num));

    std::cout << "Modified value: " << num << std::endl;

    return 0;
}

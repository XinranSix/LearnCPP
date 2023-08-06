#include <iostream>

int main(int arvc, char *argv[]) {

    // 拷贝列表初始化
    // T obj = {arg1, arg2, ...};
    // 直接列表初始化
    // T obj {arg1, arg2, ...};

    auto a = {11};
    auto b = {11, 22};

    auto c{11};
    // auto d{11, 22};

    // auto d{11, 22.33};

    return 0;
}

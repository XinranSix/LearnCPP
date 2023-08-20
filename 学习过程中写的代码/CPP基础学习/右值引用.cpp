#include <iostream>
#include <functional>

void func(int i, std::function<void(int)> f) {
    f(i);
}

void f1(int i) {
    std::cout << i << std::endl;
}
/*
函数指针
函数对象
lambda
std::function
*/

int main(int argc, char *argv[]) {

    // lambda
    auto t1 = [](int i) -> double {
        std::cout << i << std::endl;
        return 1;
    };

    int x = 10;

    func(1, [x](int i) { std::cout << x + i << std::endl; });

    return 0;
}

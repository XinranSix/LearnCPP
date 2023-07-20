#include <iostream>
#include <functional>

struct X {
    virtual void func() { std::cout << "X\n"; }
};

int main() {
    auto ptr = &X::func;
    auto func = *(int *)(&ptr);
    std::cout << func << '\n'; // 1
}
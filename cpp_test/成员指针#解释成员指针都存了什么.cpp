#include <iostream>

// 普通成员函数指针存什么？
// 证明普通的成员函数指针是存了明确的地址的，这也是必然的，所有函数都有明确地址，不然无法jmp过去

// struct X {
//     void f() { std::cout << "func\n"; }
// };

// int main() {
//     using Func = void (*)(X *const);

//     auto p = &X::f;
//     auto func = (Func)(p);
//     func(nullptr); // 打印func
// }

// 数据成员指针存什么？
// 也就印证了我们之前说的存的偏移量
struct X {
    int a, b;
    double d;
};


int main() {
    auto p = &X::a;
    auto p2 = &X::b;
    auto p3 = &X::d;
    std::cout << *reinterpret_cast<int *>(&p) << '\n';  // 0
    std::cout << *reinterpret_cast<int *>(&p2) << '\n'; // 4
    std::cout << *reinterpret_cast<int *>(&p3) << '\n'; // 8


}

// 虚成员函数指针存的什么?
// 和我们之前说的一样，和数据成员差不多，虚成员函数指针也是偏移量，当然，这是编译器的实现，标准没有规定这些东西，只规定了行为。

// struct X {
//     virtual void func() { std::cout << "X\n"; }
// };

// int main() {
//     auto ptr = &X::func;
//     auto func = *(int *)(&ptr);
//     std::cout << func << '\n'; // 1
// }
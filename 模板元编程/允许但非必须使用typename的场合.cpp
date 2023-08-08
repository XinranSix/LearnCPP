#include <iostream>
#include <functional>

// // std::unary_function<T, T*> 不是依赖性的，因为它总是一个类，不过 T
// // 最终到底是什么。

// template<typename T>
// struct something {
//     // 没问题
//     std::unary_function<T, T *> f2;
//     std::unary_function<int, int>::result_type x2;

//     // 没问题
//     std::unary_function<T, T *> f1;
//     std::unary_function<int, int>::result_type x1;
// };

int main(int arvc, char *argv[]) { return 0; }

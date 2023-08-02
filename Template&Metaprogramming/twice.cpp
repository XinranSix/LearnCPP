#include <iostream>

template<typename UnaryMetaFunctionClass, typename Arg>
struct apply1 : UnaryMetaFunctionClass::template apply<Arg> {};

// template<typename F, typename X>
// struct twice {
//     using once = apply1<F, X>::type;    // f(x)
//     using type = apply1<F, once>::type; // f(f(x))
// };

// 元函数转发
template<typename F, typename X>
struct twice : apply1<F, typename apply1<F, X>::type> {};

struct add_pointer_f {
    template<typename T>
    struct apply:boost::add_pointer<T>{};
};

int main(int arvc, char *argv[]) { return 0; }

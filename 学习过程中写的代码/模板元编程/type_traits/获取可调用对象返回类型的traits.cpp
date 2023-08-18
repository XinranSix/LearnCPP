#include <iostream>
#include <type_traits>

// 返回类型后置
template<typename F, typename Arg>
auto Func(F f, Arg arg) -> decltype(f(arg)) {
    return f(arg);
}

int fn(int) { return int(); };

using fn_ref = int (&)(int);
using fn_ptr = int (*)(int);
template<typename F, typename Arg>
using fn_type = auto(F f, Arg arg) -> decltype(f(arg));

struct fn_class {
    int operator()(int i) { return i; }
};

int main() {

    using A = std::result_of_t<decltype(fn) &(int)>; // int
    using B = std::result_of_t<fn_ref(int)>;         // int
    using C = std::result_of_t<fn_ptr(int)>;         // int
    using D = std::result_of_t<fn_class(int)>;       // int

    return 0;
}

// 需要注意 std::result_of<Fn(ArgTypes)>
// 要去Fn为一个可调用对象，而函数类型不是一个可调用对象，因此，不能使用 typedef
// std::result_of<decltype(fn)(int)>::type A:  //错误
// 需要先将fn转换为一个可调用对象类型，比如：
// typedef std::result_of<decltype(fn)&(int)>::type A;
// typedef std::result_of<decltype(fn)*(int)>::type B;
// typedef std::result_of<std::decay<decltype(fn)>::type(int)>::type C;

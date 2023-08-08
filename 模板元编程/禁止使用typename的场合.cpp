#include <iostream>

struct int_iterator {
    // typename 不能使用在模板之外的任何地方
    // using value_type = typename int;
};

/* -------------------------------------------------------------------------- */

template<typename T>
struct vector {
    // typename 也不允许用在非限定性名字上，即使它们是依赖性的
    // using value_type = typename int;
    using pair_type = typename std::pair<int, T>; // 这个好像可以，很奇怪
    // using pointer = typename T *;
};

/* -------------------------------------------------------------------------- */
// typename 不允许用于基类的名字上，即使它是依赖性的也不行：
// template<typename T>
// struct base_gen;

// struct derived : typename base_gen<T>::type {};

/* -------------------------------------------------------------------------- */
// 但下面例子中 typename 是必不可少的，因为 T::value_type 不是一个基类的名字
// template<typename T>
// struct get_value : std::unary_function<T, typename T::value_type> {};
/* -------------------------------------------------------------------------- */

int main(int arvc, char *argv[]) { return 0; }

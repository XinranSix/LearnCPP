#include <ios>
#include <iostream>
#include <type_traits>

// 在根据模板参数创建对象时，要注意移除引用：
template<typename T>
std::remove_reference_t<T> *Create() {
    using U = std::remove_reference_t<T>;
    return new U();
}
// 因为模板参数可能是引用类型，而创建对象时，需要原始的类型，不能用引用类型，所以需要将可能的引用移除

// 如果给的模板参数是一个带cv描述符的引用类型，要获取它的原始类型，可以使用decay
template<typename T>
std::decay_t<T> *Create() {
    using U = std::decay_t<T>;
    return new U();
}

// decay还可以获得函数的指针类型，从而将函数指针变量保存起来，以便在后面延迟调用。
using F = std::decay_t<int(double)>; // F为一个函数指针类型， int(*)(double)
template<typename F>
struct SimpleFunction {
    using FnType = std::decay_t<F>;
    SimpleFunction(F &f) : m_fn(f){};
    void Run() { m_fn(); }

    FnType m_fn;
};

void print(auto t) { std::cout << std::boolalpha << t << std::endl; }

int main(int arvc, char *argv[]) {

    // std::cout << std::is_same<const int, std::add_const<int>::type>::value
    //           << std::endl; // 结果为true
    // std::cout
    // << std::is_same<int, std::remove_all_extent<int[2][2][3]>::type>::value
    // << std::endl;
    print(std::is_same_v<int, std::remove_const_t<int const>>);
    print(std::is_same_v<int const, std::add_const_t<int const>>);
    print(std::is_same_v<int, std::remove_reference_t<int &>>);
    print(std::is_same_v<int, std::remove_reference_t<int &&>>);
    print(std::is_same_v<int &, std::add_lvalue_reference_t<int>>);
    print(std::is_same_v<int &&, std::add_rvalue_reference_t<int>>);
    // print(  std::boolalpha << std::is_same_v<int[3][2],
    // std::remove_all_extent_t<int[3][3][2]>> );
    print(std::is_same_v<int[4][5], std::remove_extent_t<int[3][4][5]>>);
    print(std::is_same_v<int, std::remove_pointer_t<int *>>);
    print(std::is_same_v<int **, std::add_pointer_t<int *>>);
    print(std::is_same_v<int, std::decay_t<int const>>);
    print(std::is_same_v<int, std::decay_t<int volatile>>);
    print(std::is_same_v<int *, std::decay_t<int[]>>);

    using T = std::common_type_t<int, double, bool, float>;

    T a{1};
    T b{1.0};
    T c{true};
    T d{1.0f};

    return 0;
}

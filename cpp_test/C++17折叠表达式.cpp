#include <iostream>
#include <utility>
#include <vector>

/* -------------------------------------------------------------------------- */
template<size_t... args>
constexpr int v = (args - ...);

template<size_t... args>
constexpr int v2 = (... - args);

template<class... Args>
void printer(Args &&...args) {
    (std::cout << ... << args) << '\n';
}

template<class... Args>
void print(Args... args) {
    ((std::cout << args << ' '), ...);
}
/* -------------------------------------------------------------------------- */

// 【翻译】折叠表达式实用技巧
//  假设你需要一个能将所有参数相加的变参函数，在C++17以前，你需要这样两个“递归”函数：

// template<typename H>
// auto add(H head) {
//     return head;
// }

// template<typename H, typename... T>
// auto add(H head, T... tail) {
//     return head + add(tail...);
// }

// C++17新增了折叠表达式，现在你只需要一行就能搞定：
template<typename H, typename... T>
auto add(H head, T... tail) {
    return (head + ... + tail);
    // expands to: head + tail[0] + tail[1] + ...
}
// 对每个元素调用一次函数

void f(int e) {}

template<typename... Args>
void test01(Args... ts) {
    // for (int i : ts) {
    //     f(i);
    // }
    // (f(ts), ...);
    // expands to: f(ts[0]), f(ts[1]), f(ts[2]), ...
}

/* -------------------------------------------------------------------------- */
// https://zhuanlan.zhihu.com/p/625884960?utm_medium=social&utm_oi=1040949215538733056&utm_psn=1670044313781190658&utm_source=ZHShareTargetIDMore
// C++ 17 折叠表达式
/*
四种形式：
Unary right fold (E op ...) becomes (E1 op (... op (EN-1 op EN)))
Unary left fold (... op E) becomes (((E1 op E2) op ...) op EN)
Binary right fold (E op ... op I)becomes(E1 op (... op (EN−1 op (EN op I))))
Binary left fold(I op ... op E)becomes ((((I op E1) op E2) op ...) op EN)
*/

// 最基本操作 - 尾递归改折叠表达式
template<class Target>
bool In(Target &&) {
    return false;
}

template<class Target, class First, class... Args>
bool In(Target &&t, First &&f, Args &&...args) {
    return t == f || In(std::forward<Target>(t), std::forward<Args>(args)...);
}
// 折叠表达式版本
template<class Target, class... Args>
bool In(Target &&t, Args &&...args) {
    return ((t == args) || ...);
}

/*
来点高级的
, 操作符
比如我要检查几个变量必须严格递减
a >= b >= c ... ,
cpp不支持这样连写运算符，使用折叠表达式就可以写成下面的形式
*/
template<typename Arg0, typename... Args>
bool isDecrease(const Arg0 &a0, const Args &...args) {
    using CommonType = std::common_type_t<Arg0, Args...>;

    CommonType tmp0 = a0;
    CommonType tmp1 = a0;
    return ((tmp0 = tmp1, tmp1 = args, tmp0 >= tmp1) && ...);
}

/*
反向执行
前面都是顺序执行参数包，那如何反向执行？
参考求值顺序 https://en.cppreference.com/w/cpp/language/eval_order 规则20 ，((a
= f1()) = f2()) = f3() 顺序一定是 f3 2 1 , 所以我们只需要写成 (a = ...
(f(args))) 即可，无返回值的使用, 操作符 塞个临时变量。 比如逆序构造一个 vector
*/
template<typename... Args>
auto Reverse(Args &...args) {
    std::vector<std::common_type_t<Args...>> res{};
    bool tmp{false};
    (tmp = ... = (res.push_back(args), false));
    /*
     (tmp = (res.push_back(args0), false) = (res.push_back(args1), false)...);
    */
    return res;
}

/*
避免滥用
c++
最大的问题就是过于灵活，一个问题有N多种解法，有时候需要想一想，这样真的好吗？

比如下面的例子，在std::tuple中查找某个类型是否存在并返回其index
(偶尔看到，不是我写的)
*/

// template<typename Tuple, typename Item>
// consteval size_t tuple_index() {
//     const auto helper = []<typename... Args>(std::tuple<Args...> *) {
//         size_t i = 0;
//         [[maybe_unused]] auto _ =
//             ((++i, std::is_same_v<Args, Item>) || ... || ++i);
//         return i - 1;
//     };
//     return helper(static_cast<Tuple *>(nullptr));
// }

// 相比传统的递归写法并不直观
// template<class T, class Item, std::size_t I = 0>
// consteval size_t TupleIndex() {
//     if constexpr (I >= std::tuple_size_v<T>) {
//         return I;
//     } else if constexpr (std::is_same_v<std::tuple_element_t<I, T>, Item>) {
//         return I;
//     } else {
//         return TupleIndex<T, Item, I + 1>();
//     }
// }

/* -------------------------------------------------------------------------- */
// C++ 学习：折叠表达式
/*
一元左折叠
(... op args)

展开：((arg1 op arg2) op arg3) op ...

一元右折叠
(args op ...)

展开：arg1 op (arg2 op ... (argN-1 op argN))
*/

/*
示例1
减法运算，此处加constexpr只为观察方便，可以不加
*/

template<bool f, class... T>
constexpr auto sub_(const T &...args) {
    if (f) {
        return (... - args);
    } else {
        return (args - ...);
    }
}

void test02() {
    constexpr int a = sub_<true>(10, 2, 3, 4);
    constexpr int b = sub_<false>(10, 2, 3, 4);
    std::cout << a << std::endl;
    std::cout << b << std::endl;
}

/*
二元左折叠
(value op ... op args)
展开：(((value op arg1) op arg2) op arg3) op ...

二元右折叠
(args op ... op value)
展开：arg1 op (arg2 op (arg3 op ... (argN op value)))
*/
template<bool f, class U, class... T>
constexpr auto sub_1(const U &val, const T &...args) {
    if (f) {
        return (val - ... - args);
    } else {
        return (args - ... - val);
    }
}

void test03() {
    constexpr int a1 = sub_1<true>(20, 5, 3, 2);
    constexpr int b1 = sub_1<false>(20, 5, 3, 2);
    std::cout << a1 << std::endl;
    std::cout << b1 << std::endl;
}

/*
示例3 print
*/
template<typename... T>
void print_(const T &...arg) {
    (std::cout << ... << arg);
}

/*
示例4 逗号运算符，每个参数调用函数
*/

template<typename Func, typename... T>
void invoke_(Func func, const T &...val) {
    (..., func(val));
}

void test05() {
    invoke_([](int x) { std::cout << "x = " << x << std::endl; }, 1, 2, 3, 4, 5,
            6);
}

void test04() { print_(1, 'c', "kkk", 45, '\n'); }

int main(int argc, char **argv) {

    test02();
    test03();
    test04();
    test05();

    return 0;
}

## 元编程基础

元函数较为接近数学的定义为：是一个无副作用的映射或变换，即在输入相同的前提下，多次调用同一个函数，得到的结果也是相同的。

元函数会在编译器被调用。

编译阶段，编译器只能构造常量作为中间结果，无法构造并维护可以记录系统状态并随着改变的量，因此编译器可以使用的函数只能是无副作用的函数。

例如下面这个函数可以作为元函数使用：

```cpp
constexpr int fun(int a) { return a + 1; }
```

而下面的代码不能通过编译：

```cpp
static int call_count = 3;
constexpr int fun2(int a) { return a + (call_count++); }
```

从某一角度来看，元函数可以分为数值元函数和类型元函数，上面的 `fun` 视为数组元函数。

类型元函数用的比数值元函数多。

### 类型元函数

一个函数（映射）从数学的角度来定义：

$$
y = f\left(x\right)
$$

元编程的核心是元函数，元函数的输入、输出的形式可以有很多种，可以是数值类型，也可以将 C++ 的数据类型作为函数的输出与输入。

例如下面的元函数将 `int` 和 `long` 转换为对应的无符号类型，如果不是这两个类型则直接返回原类型。

```cpp
template<typename T>
struct Fun_ {
    using type = T;
};

template<>
struct Fun_<int> {
    using type = unsigned int;
};

template<>
struct Fun_<long> {
    using type = unsigned long;
};

template<typename T>
using Fun = typename Fun_<T>::type;

Fun_<int>::type h = 3;
```

在上古神作《C++ 模板元编程》一书中（现在有点过时了这书），将类模板 `Fun_` 视为元函数，当输入为 `X` 时，输出为 `Fun_<X>::type`，同时，该书规定了所讨论的元函数的输入和输出均是类型。

在《C++ 模板元编程》中，将一个包含了 `type` 声明的类模板视为元函数，这一定义并非不好（统一了接口，带来了设计上的便利性），但过于狭隘。

将元函数定义为：

- 不限制映射的表示方法，例如以 `constexpr` 开头的函数，已经提供内嵌 `type` 类型的模板，以及后文讨论的其他形式的「函数」，只要其无副作用，同时可以在编译器被调用，都可以视为元函数。
- 不限制输入与输出的形式，输入与输出可以是数值、类型、模板等等。

```cpp
template<typename T>
using Fun = typename Fun_<T>::type;

Fun<int> h = 3;
```

`Fun` 如果按照《C++ 模板元编程》中的定义，它表示一个标准的元函数，原因在于其没有内嵌类型 `type`，但根据我们的定义，它应该被视为一个元函数。

在标准库中，也是有这种方式来定义元函数，例如，在 C++ 11 中定义了元函数 `std::enable_if`，而在 C++ 14 引入了 定义 `std::enable_if_t`，它们的关系大致为：

```cpp
template <typename>
using enable_if_t = typename enable_if<T>::type
```

> 实际上，在 C++ 14 中对 C++ 11 中的元函数做了「增强」，例如 `std::xxx<X>::type` 可以通过 `std::xxx_t<X>` 代替，`std::xxx<X>::value` 可以通过 `std::xxx_v<X>` 代替。

### 各种各样的元函数

一切「无副作用」的、可以在编译器被调用，用于对编译器甚乃至运行期的程序行为产生影响，那么这个映射都可以称为元函数，其表现形式千变万化。

实际上，一个模板就是一个元函数。例如，下面这个类模板就是一个元函数，它接受一个输入 `T`，输出为 `Fun<T>`

```cpp
template<typename T>
struct Fun {};
```

我们可以建立无参元函数：

```cpp
// 无参，返回值为 int
struct Fun {
    using type = int;
}

// 无参，返回值为 10
constexpr int fun() {
    return 10;
}
```

可以使用 C++ 14 中对 `constexpr` 的拓展来构建元函数：

```cpp
template <int a> 
constexpr int fun = a + 1;
```

元函数可以有多个返回值：

```cpp
template <>
struct Fun_<int> {
    using reference_type = int &;
    using const_reference_type = const int &;
    using value_type = int;
}
```

### type_traits

type_traits 是一个元函数库，由 boost 引入（可参考《C++ 模板元编程》），C++ 11 被标准吸收，C++ 14 得到加强，需引入头文件 `type_traits` 来引入。这个库实现类类型转换、类型比较与判断等功能。

可参考：https://www.cnblogs.com/gtarcoder/p/4807670.html

下面几个例子可以参考一下：

```cpp
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
```

命名约定：如果元函数的返回值要用某种依赖性的名称表示，那么函数将被命名为 `XXX_` 的形式；反之，如果元函数的返回值可以字节用某种非依赖性的名称表示，那么元函数的名称将不包含下划线形式的后缀，例如：

```cpp
template <int a, int b>
struct Add_ {
    constexpr static int value = a + b;
};

template <int a, int b>
constexpr int Add = a + b;

constexpr int x1 = Add_<2, 3>::value;
constexpr int x2 = Add<2, 3>;
```

### 模板型模板参数

#### 模板作为容器的输入

例如：

```cpp
template <template <typename> class T1, typename T2>
struct Fun_ {
    using type = typename T1<T2>::type;
};

template <template <typename> class T1, typename T2>
using Fun = typename Fun_<T1, T2>::type;

Fun<std::remove_reference, int&> h = 3;
```

#### 模板作为元函数的输出

例如：

```cpp
template <bool AddOrRemoveRef> struct Fun_;

template <>
struct Fun_<true> {
    template <typename T>
    using type = std::add_lvalue_reference<T>;
};

template <>
struct Fun_<false> {
    template <typename T>
    using type = std::remove_reference<T>;
};

template <typename T>
template <bool AddOrRemove>
using Fun = typename Fun_<AddOrRemove>::template type<T>;

template <typename T>
using Res_ = Fun<false>;

Res_<int&>::type h = 3;
```

### 容器模板

我们的容器也仅能保存一种类别的操作数，比如一个仅能保存数值的容器，或者仅能保存类型的容器，或者仅能保存模板的容器。

使用 C++ 11 中引入的变参数模板，可以很容易实现我们想要的功能。

```cpp
template <int... Vals>
struct InContainer;

template <bool... Vals>
struct BoolContainer;

template <typename... Types> 
struct TypeContainer;

template <template <typename> class... T> 
struct TemplateCont;

template <template <typename...> class...T>
struct TemplateCont2;
```

> 元编程中有一个惯用法，就是仅在必要时才引入定义。

### 顺序、分支与循环代码的编写

#### 顺序执行的代码

例如：

```cpp
template <typename T>
struct RemoveReferenceConst_ {
private:
    using inter_type = std::remove_reference_t<T>;
public:
    using type = std::remove_const_t<inter_type>;
};

template <typename T>
using RemoveReferenceConst = typename RemoveReferenceConst_<T>::type;

RemoveReferenceConst<const int&> h = 3;
```

#### 分支执行的代码

使用模板特化或部分特化来实现分支，是一种非常常见的手段，当然也有些其他手段。

**使用 `std::conditional` 与 `std::conditional_t` 实现分支**

例如：

```cpp
std::conditional<true, int, float>::type x = 3;
std::conditional_y<false, int, float> y = 1.0f;
```

这种方法只能实现简单的分支。

**使用（部分）特化实现分支**

特化天生就是来引入差异的，因此，使用它来实现分支也十分自然。

例如：

```cpp
struct A;
struct B;

template <typename T>
struct Fun_ {
    constexpr static size_t value = 0;
};

template <>
struct Fun_<A> {
    constexpr static size_t value = 1;
};

template <>
struct Fun_<B> {
    constexpr static size_t value = 2;
};

constexpr size_t h = Fun_<B>::value;
```

再例如：

```cpp
struct A;
struct B;

template <typename T>
constexpr size_t Fun = 0;

template <>
constexpr size_t Fun<A> = 1;

constexpr size_t Fun<B> = 2;

constexpr size_t h = Fun<B>;
```

> 注意，在非完全特化的类模板中引入完全特化的代码是非法的，例如：

```cpp
template <typename TW>
struct Wrapper {
    template <typename T>
    struct Fun_ {
        constexpr static size_t value = 0;
    };

    template <>
    struct Fun_<int> {
        constexpr static size_t value = 1;
    };
};
```

酱紫的代码是不行的，我们可以酱紫修改：

```cpp
template <typename TW>
struct Wrapper {
    template <typename T, typename TDummy = void>
    struct Fun_ {
        constexpr static size_t value = 0;
    };

    template <typename TDummy>
    struct Fun_<int, TDummy> {
        constexpr static size_t value = 1;
    }
};
```

**使用 `std::enable_if` 与 `std::enable_if_t` 实现分支**

例如：

```cpp
template <bool IsFeedbackOut, typename T, std::enable_if_t<IsFeedbackOut>* = nullptr>
auto FeedbackOut_(T&&) { /* ... */ }

template <bool IsFeedbackOut, typename T, std::enable_if_t<!IsFeedbackOut>* = nullptr>
auto FeedbackOut_(T&&) { /* ... */ }
``` 

当 `FeedbackOut_` 为真时，`std::enable_if_t<IsFeedbackOut>::type` 是有意义的，这使得第一个函数匹配成功；与之对应的，第二个函数匹配是失败的。反之，当 `FeedbackOut_` 为假时，`std::enable_if_t<!IsFeedbackOut>::type` 是有意义的，这就使得第二个函数匹配成功，第一个函数匹配失败。

**编译期分支与多种返回类型**

例如：

```cpp
auto wrap1(bool Check) {
    if (Check) {
        (int) 0;
    } else {
        return (double) 0;
    }
}
```

是编译不过去的，我们可以酱紫做：

```cpp
template <bool Check, std::enable_if_t<Check>* = nullptr>
auto fun() {
    return (int) 0;
};

template <bool Check, std::enable_if_t<!Check>* = nullptr>
auto fun() {
    return (double) 0;
}

template <bool Check>
auto wrap2() {
    return fun<Check>();
}

int main() {

    std::cerr << wrap2<true>() << std::endl;

    return 0;
}
```

可以使用 C++ 17 引入的 `if constexpr` 来简化代码：

```cpp
template <bool Check>
auto fun() {
    if constexpr (Check) {
        return (int) 0;
    } else {
        return (double) 0;
    }
}

int main() {

    std::cerr << fun<true>() << std::endl;

    return 0;
}
```

**执行循环的代码**

在编译器，我们往往使用递归来实现循环。

例如，给定一个无符号整数，求该整数所对应的二进制中 1 的个数：

```cpp
template <size_t Input>
constexpr size_t OnesCount = (Input % 2) + OnesCount<Input / 2>;

template <>
constexpr size_t OnesCount<0> = 0;

constexpr size_t res = OnesCount<45>;
```

下面是处理数组的例子：

```cpp
template <szie_t...Inputs>
constexpr size_t Accumulate = 0;

template <size_t CurInput, size_t...Inputs>
constexpr size_t Accumulate<CurInput, Inputs...> = CurInput + Accumulate<Inputs...>;

constexpr size_t = res = Accumulate<1, 2, 3, 4, 5>;
```

或者使用 C++ 17 引入的折叠表达式：

```cpp
template <size_t values>
constexpr size_t fun() {
    return (0 + ... + values);
}

constexpr size_t res = fun<1, 2, 3, 4, 5>();
```

### 分支选择与短路逻辑

减少编译器实例化的另外一种主要的技术就是引入短路逻辑，例如：

```cpp
template <size_t N>
constexpr bool is_odd = ((N % 2) == 1);

template <size_t N>
struct AllOdd_ {
    constexpr static bool is_cur_odd = is_odd<N>;
    constexpr static bool is_pre_odd = AllOdd_<N-1>::value;
    constexpr static bool value = is_cur_odd && is_pre_odd;
};

template <>
struct AllOdd_<0> {
    constexpr static bool value = is_odd<0>;
};
```

改进版本如下：

```cpp
template <bool cur, typename TNext>
constexpr static bool AndValue = false;

template <typename TNext>
constexpr static bool AndValue<true, TNext> = TNext::value;

template <size_t N>
constexpr bool is_odd = ((N % 2) == 1);

template <size_t N>
struct AllOdd_ {
    constexpr static bool is_cur_odd = is_odd<N>;
    constexpr static bool value = AndValue<is_cur_odd, AllOdd_<N - 1>>;
};

template <>
struct AllOdd_<0> {
    constexpr static bool value = is_odd<0>;
};
```

### 奇特的递归模板

CRTP 是一种派生类的什么方式，其「奇特」之处在于：派生类会将本身作为模板参数传递给其基类，例如：

```cpp
template <typename D>
class Base { /*...*/ }

class Derived : public Base<Derived> { /*...*/ };
```

CRTP 的典型应用场景是模拟虚函数，例如：

```cpp
template <typename D>
struct Base {
    template <typename T1>
    void Fun(const T1& input) {
        D* ptr = static_cast<D*>(this);
        this->Imp(input);
    }
};

template Derive : public Base<Derive> {
    template <typename T1> 
    void Imp(T1 const& input) {
        std::cout << input << endl;
    }
};
```

在这个代码中，基类 `Base<D>` 会假定派生类实现类一个接口 `Imp`，会在其函数 `Fun` 中调用这个接口。如果采用面向对象的编程方法，我们需要引入虚函数 `Imp`。但是，`Imp` 是一个函数模板，无法被声明为虚函数，这里可以借助 `CRTP` 技术实现：

```cpp
template <typename D>
struct Base {
    static void Fun() {
        D::Imp();
    }
};

struct Derive : public Base<Derive> {
    static void Imp() {
        std::cout << "Implementation from derive class" << std::endl;
    }
};

int main() {

    Derive:Fun();

    return 0;
}
```

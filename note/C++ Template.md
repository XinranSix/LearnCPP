## 第一部分

### 函数模板

下面就是一个返回两个值中最大者的函数模板：

```cpp
template<typename T>
inline T const &max(T const &a, T const &b) {
    return a < b ? b : a;
}
```

在上面程序中，类型参数是 `T`，类型 `T` 需要支持 `operator<`，因为 a 和 b 就是使用这个运算符来比较大小的。

从语义上讲，这里使用 `class` 和 `typename` 是等价的，但是，`class` 的这种用法往往会给人误导，这里的 `class` 并不意味着只有类才能被用来替代 `T`，事实上基本类型也可以，所以尽量使用 `typename`.

使用上面的 `max()` 函数模板：

```cpp
#include <iostream>
#include <complex>
#include <string>
#include "max.hpp"

int main(int arvc, char *argv[]) {

    int i = 42;
    std::cout << "max(7, i): " << ::max(7, i) << std::endl;

    double f1 = 3.4;
    double f2 = -6.7;

    std::cout << "max(f1, f2): " << ::max(f1, f2) << std::endl;

    std::string s1 = "mathematics";
    std::string s2 = "math";
    std::cout << "max(s1, s2): " << ::max(s1, s2) << std::endl;

    return 0;
}
```

用具体类型代替模板参数的过程叫做实例化，它产生了一个模板的实例。可以看到：只要使用函数模板，编译器会自动地引发这样一个实例化过程，因此程序员并不需要额外地请求模板的实例化。

如果试图基于一个不支持模板内部所使用操作的类型实例化一个模板，那么将会导致一个编译期错误，例如：

```cpp
std::complex<float> c1, c2; //std::complex 并 不 支 持 operator <
max(c1, c2); //编译器错误
```

于是，我们可以得出一个结论：模板被编译了两次，分别发生在：

1. 实例化之前，先检查模板代码本身，查看语法是否正确；在这里会发现错误的语法，如遗漏分号等。
2. 在实例化期间，检查模板代码，查看是否所有的调用都有效。在这里会发现无效的调用，如该实例化类型不支持某些函数调用等。

当使用函数模板，并且引发模板实例化的时候，编译器（在某时刻）需要查看模板的定义。这就不同于普通函数中编译和链接之间的区别，因为对于普通函数而言，只要有该函数的声明（即不需要定义），就可以顺利通过编译。后面再给出解决这个问题的方法，这里先使用内联函数，只在头文件内部实现每个模板。

#### 实参的演绎

当我们为某些实参调用一个诸如 `max()` 的模板时，模板参数可以由我们所传递的实参来决定。如果我们传递了两个 `int` 给参数类型 `T const&`，那么 C++ 编译器能够得出结论：`T` 必须是 `int`.

注意，这里不允许进行自动类型转换；每个 `T` 都必须正确地匹配，例如：

```cpp
template <typename T>
inline T const& max (T const& a, T const& b);

::max(4, 7) //OK: 两个实参的类型都是 int
::max(4, 4.2) //ERROR:第 1 个 T 是 int，而第 2 个 T 是 double
```

有 3 种方法可以用来处理上面这个错误：
1. 对实参进行强制类型转换，使它们可以互相匹配：`max ( static_cast<double>(4),4.2)`
`max<double>(4,4.2)` //OK
2. 显式指定（或者限定）T 的类型：
3. 指定两个参数可以具有不同的类型。
前面两种方法如下：

```cpp
::max(static_cast<double>(4), 4.2);
::max<double>(4, 4.2);
```

#### 模板参数

函数模板有两种类型的参数：

1. 模板参数。
2. 调用参数。

```cpp
// 下面函数模板中，T 是模板参数，a 和 b 都是调用参数
template <typename T>
T max(T const& a, T const& b);
```

你可以根据需要声明任意数量的模板参数，例如，你可以声明如下函数模板：

```cpp
template<typename T1, typename T2>
inline T1 max(T1 const &a, T2 const &b) {
    return a < b ? b : a;
}
```

把第 2 个参数转型为返回类型的过程将会创建一个新的局部临时对象，这导致了你不能通过引用来返回结果。因此，在上面的例子里，返回类型必须是 `T1`，而不能是 `T1 const&`.

> 注意：在函数模板内部，不能指定默认模板实参，这于类模板不一样。
>
> 再注意：C++ 11 标准中已经允许函数模板使用默认参数。

因为调用参数的类型构造自模板参数，所以模板参数和调用参数通常是相关的。我们把这个概念称为：函数模板的**实参演绎**，它让你可以像调用普通函数那样调用函数模板。

当模板参数和调用参数没有发生关联，或者不能由调用参数来决定模板参数的时候，你在调用时就必须显式指定模板实参，例如：

```cpp
template <typename T1, typename T2, typename RT>
inline RT max(T1 const& a, T2 const& b) {
    return a < b ? b : a;
}

::max<int, double, double>(4,4.2) //OK, 但是很麻烦
```

如果你改变模板参数的声明顺序，那么调用时就只需要指定返回类型：

```cpp
template <typename RT, typename T1, typename T2>
inline RT max (T1 const& a, T2 const& b) {
    return a < b ? b : a;
}
...
max<double>(4, 4.2) //OK: 返回类型是double，其他两个类型演绎为 int 和 double.
```

#### 重载函数模板

和普通函数一样，函数模板也可被重载，例如：

```cpp
#include <iostream>

inline int const &max(int const &a, int const &b) { return a < b ? b : a; }

template<typename T>
inline T const &max(T const &a, T const &b) {
    return a < b ? b : a;
}

template<typename T>
inline T const &max(T const &a, T const &b, T const &c) {
    return ::max(::max(a, b), c);
}

int main(int arvc, char *argv[]) {

    ::max(7, 24, 68);
    ::max(7.0, 42.0);
    ::max('a', 'b');
    ::max(7, 42);
    ::max<>(7, 42);
    ::max<double>(7, 42);
    ::max('a', 42.7);

    return 0;
}
```

记住：

1. 对于非模板函数和同名的函数模板，如果其他条件都是相同的话，那么在调用的时候，重载解析过程通常会调用非模板函数，而不会从该模板产生出一个实例。
2. 模板不允许自动类型转化，普通函数可以进行自动类型转换。

下面这个例子指针和普通的 C 字符串重载这个求最大值的模板：

```cpp
#include <iostream>
#include <cstring>
#include <string>

template<typename T>
inline T const &max(T const &a, T const &b) {
    return a < b ? b : a;
}

template<typename T>
inline T *const &max(T *const &a, T *const &b) {
    return *a < *b ? b : a;
}

inline char const *const &max(char const *const &a, char const *const &b) {
    return std::strcmp(a, b) < 0 ? b : a;
}

int main(int arvc, char *argv[]) {

    int a = 7;
    int b = 42;
    std::string s = "hey";
    std::string t = "you";
    ::max(s, t);

    int *p1 = &b;
    int *p2 = &a;
    ::max(p1, p2);
    char const *s1 = "David";
    char const *s2 = "Nico";
    ::max(s1, s2);

    return 0;
}
```

> 注意：在所有重载的实现里面，我们都是通过引用来传递每个实参的。一般而言，在重载函数模板的时候，值改变参数的数目或者显式地指定模板参数，否则就可能会出现非预期的结果，例如下面的程序就会发生错误：

```cpp
#include <iostream>
#include <cstring>
#include <string>

template<typename T>
inline T const &max(T const &a, T const &b) {
    return a < b ? b : a;
}

inline char const *max(char const *a, char const *b) {
    return std::strcmp(a, b) < 0 ? b : a;
}

template<typename T>
inline T const &max(T const &a, T const &b, T const &c) {
    return max(max(a, b), c);
}

int main(int arvc, char *argv[]) {

    ::max(7, 42, 68);
    const char *s1 = "frederic";
    const char *s2 = "anica";
    const char *s3 = "lucas";
    ::max(s1, s2, s3); // 错误

    return 0;
}
```

当调用重载函数的时候，调用结果就有可能与该重载函数在此时可见与否这个事实有关，但也可能没有关系。事实上，定义一个具有 3 个参数的 `max()` 版本，而且直到该定义处还没有看到一个具有两个 `int` 参数的重载 `max()` 版本的声明；那么这个具有 3 个 `int` 实参的 `max()` 调用将会使用具有 2 个参数的模板，而不会使用基于 `int` 的重载版本 `max()`：

```cpp
#include <iostream>

template<typename T>
inline T const &max(T const &a, T const &b) {
    return a < b ? b : a;
}

template<typename T>
inline T const &max(T const &a, T const &b, T const &c) {
    return max(max(a, b), c);
}

inline int const &max(int const &a, int const &b) { return a < b ? b : a; }

int main(int arvc, char *argv[]) { return 0; }
```

> 目前来说：函数的所有重载版本的声明都应该位于该函数被调用的位置之前。

#### 小结

- 模板函数为不同的模板实参定义了一个函数家族。
- 当你传递模板实参的时候，可以根据实参的类型来对函数模板进行实例化。
- 你可以显式指定模板参数。
- 你可以重载函数模板。
- 当重载函数模板的时候，把你的改变限制在：显式地指定模板参数。
- 一定要让函数模板的所有重载版本的声明都位于它们被调用的位置之前。

### 类模板





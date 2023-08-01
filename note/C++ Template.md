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

下面是一个基于类模板的 `Stack` 类的：

```cpp
#include <vector>
#include <stdexcept>

template<typename T>

class Stack {
private:
    std::vector<T> elems;

public:
    void push(T const &);
    void pop();
    T top() const;
    bool empty() const { return elems.empty(); }
};

template<typename T>
void Stack<T>::push(T const &elem) {
    elems.push_back(elem);
}

template<typename T>
void Stack<T>::pop() {
    if (elems.empty()) {
        throw std::out_of_range("Stack<>::pop: empty stack");
    }
    elems.pop_back();
}

template<typename T>
T Stack<T>::top() const {
    if (elems.empty()) {
        throw std::out_of_range("Stack<>::top empty stack");
    }
    return elems.back();
}
```

#### 类模板的声明

类模板的声明和函数模板的声明很相似：在声明之前，我们先
声明作为类型参数的标识符：

```cpp
template <typename T>
class Stack {
};
```

在类模板的内部，`T`` 可以像其他任何类型一样，用于声明成员变量和成员函数。

这个类的类型是 `Stack<T>`，其中 `T` 是模板参数。因此，当在声明中需要使用该类的类型时，你必须使 `Stack<T>`. 例如，如果你要声明自己实现的拷贝构造函数和赋值运算符，那么应该这样编写：

```cpp
template <typename T>
class Stack {
    Stack (Stack<T> const&); 
    Stack<T>& operator= (Stack<T> const&); 
};
```

当使用类名而不是类的类型时，就应该只用 `Stack`，例如：当你指定类的名称、类的构造函数、析构函数时，就应该使用 `Stack`.

#### 成员函数的实现

为了定义类模板的成员函数，你必须指定该成员函数是一个函数
模板，而且你还需要使用这个类模板的完整类型限定符。类型 `Stack<T>` 的成员函数 `push()` 的实现如下：

```cpp
template <typename T>
void Stack<T>::push (T const& elem) {
    elems.push_back(elem); 
}
```

#### 类模板Stack的使用

注意，只有那些被调用的成员函数，才会产生这些函数的实例化代码。对于类模板，成员函数只有在被使用的时候才会被实例化。显然，这样可以节省空间和时间；另一个好处是：对于那些「未能提供所有成员函数中所有操作的」类型，你也可以使用该类型来实例化类模板，只要对那些“未能提供某些操作的”成员函数，模板内部不使用就可以。

你可以像使用其他任何类型一样地使用实例化后的类模板类型（如 `Stack<int>`），只要它支持所调用的操作就可以：

```cpp
void foo(Stack<int> const& s) {
    Stack<int> istack[10];
}
```

<font style="color: red">模板实参可以是任何类型，诸如指向浮点型的指针，唯一的要求就是：该类型必须提供被调用的所有操作。</font>

> 注意，再 C++ 98 时代，诸如 `vector<vector<int>>` 酱紫的代码会出现问题，原因在于后面的 `>>` 会被解析为右移运算符，所以要写成 `vector<vector<int> >`，但在 C++ 11 之后没有这种限制了。

#### 类模板的特化

可以用模板实参来特化类模板。和函数模板的重载类似，通过特化类模板，你可以优化基于某种特定类型的实现，或者克服某种特定类型在实例化类模板时所出现的不足。另外，如果要特化一个类模板，**你还要特化该类模板的所有成员函数**。虽然也可以只特化某个成员函数，但这个做法并没有特化整个类，也就没有特化整个类模板。

为了特化一个类模板，你必须在起始处声明一个 `template<>`，接下来声明用来特化类模板的类型。这个类型被用作模板实参，且必须在类名的后面直接指定：

```cpp
template<>
class Stack<std::string> {
}
```

进行类模板的特化时，每个成员函数都必须重新定义为普通函
数，原来模板函数中的每个 `T` 也相应地被进行特化的类型取代：

```cpp
void Stack<std::string>::push (std::string const& elem){
    elems.push_back(elem); 
}
```

下面是一个用 `std::string` 特化 `Stack<>` 的完整例子：

```cpp
#include <deque>
#include <string>
#include <stdexcept>
#include "stack1.hpp"

template<>
class Stack<std::string> {
private:
    std::deque<std::string> elems; // 包含元素的容器
public:
    void push(std::string const &); // 压入元素
    void pop();                     // 弹出元素
    std::string top() const;        // 返回栈顶元素
    bool empty() const {            // 返回栈是否为空
        return elems.empty();
    }
};

void Stack<std::string>::push(std::string const &elem) {
    elems.push_back(elem); // 把传入的实参elem附加到末端
}

void Stack<std::string>::pop() {
    if (elems.empty()) {
        throw std::out_of_range("Stack<std::string>::pop(): empty stack");
    }
    elems.pop_back(); // 删除末端元素
}

std::string Stack<std::string>::top() const {
    if (elems.empty()) {
        throw std::out_of_range("Stack<std::string>::top(): empty stack");
    }
    return elems.back(); // 返回末端元素的拷贝
}
```

可以看到：特化的实现可以和基本类模板的实现完全不同

####  局部特化

类模板可以被局部特化。例如类模板：

```cpp
template <typename T1, typename T2>
class MyClass {
};
```

就可以有下面几种局部特化：

```cpp
//局部特化：两个模板参数具有相同的类型
template <typename T>
class MyClass<T,T> {
};

//局部特化：第2个模板参数的类型是int
template<typename T>
class MyClass<T,int> {
};

//局部特化：两个模板参数都是指针类型。
template<typename T1,typename T2>
class MyClass<T1*,T2*>{
};
```

下面的例子展示各种声明会使用哪个模板：

```cpp
Myclass<int, float> mif; //使用MyClass<T1,T2>
MyClass<float, float> mff; //使用MyClass<T,T>
MyClass<float, int> mfi; //使用MyClass<T,int>
MyClass<int*, float*> mp; //使用MyClass<T1*,T2*>
```

如果有多个局部特化同等程度地匹配某个声明，那么就称该声明具有二义性：

```cpp
MyClass<int,int> m; // 错误：同等程度地匹配 MyClass<T, T> 和 MyClass<T, int>
MyClass<int*, int*> m; // 错误: 同等程度地匹配 MyClass<T, T> 和MyClass<T1*, T2*>
```

为了解决第 2 种二义性，你可以另外提供一个指向相同类型指针的特化：

```cpp
template<typename T>
class MyClass<T*, T*> {
};
```

#### 缺省模板实参

对于类模板，你还可以为模板参数定义缺省值；这些值就被称为
缺省模板实参；而且，它们还可以引用之前的模板参数，例如：

> 注意：C++ 11 之后函数模板可以有默认值。

```cpp
#include <vector>
#include <stdexcept>

template<typename T, typename CONT = std::vector<T>>
class Stack {
private:
    CONT elems;

public:
    void push(T const &);
    void pop();
    T top() const;
    bool empty() const { return elems.empty(); }
};

template<typename T, typename CONT>
void Stack<T, CONT>::push(T const &elem) {
    elems.push_back(elem);
}

template<typename T, typename CONT>
void Stack<T, CONT>::pop() {
    if (elems.empty()) {
        throw std::out_of_range("Stack<>::pop(): empty stack");
    }
    elems.pop_back();
}

template<typename T, typename CONT>
T Stack<T, CONT>::top() const {
    if (elems.empty()) {
        throw std::out_of_range("Stack<>::top empty stackF");
    }
    return elems.back();
}
```

使用如下：

```cpp
#include <exception>
#include <iostream>
#include <deque>
#include <cstdlib>
#include "stack3.hpp"

int main(int arvc, char *argv[]) {

    try {
        Stack<int> intStack;
        Stack<double, std::deque<double>> dblStack;
        intStack.push(7);
        std::cout << intStack.top() << std::endl;
        intStack.pop();
        dblStack.push(42.42);
        std::cout << dblStack.top() << std::endl;
        dblStack.pop();
        dblStack.pop();
    } catch (std::exception const &ex) {
        std::cerr << "Exception: " << ex.what() << std::endl;
        return EXIT_FAILURE;
    }

    return 0;
}
```

#### 小结

1. 类模板是具有如下性质的类：在类的实现中，可以有一个或多个类型还没有被指定。
2. 为了使用类模板，你可以传入某个具体类型作为模板实参；然后编译器将会基于该类型来实例化类模板。
3. 对于类模板而言，只有那些被调用的成员函数才会被实例化。
4. 你可以用某种特定类型特化类模板。
5. 你可以用某种特定类型局部特化类模板。
6. 你可以为类模板的参数定义缺省值，这些值还可以引用之前的模板参数。


### 非类型模板参数

普通值也可以作为模板参数。

#### 非类型的类模板参数

例如，把数组大小定义为一个模板参数：

```cpp
#include <stdexcept>

template<typename T, int MAXSIZE = 100>
class Stack {
    T elems[MAXSIZE];
    int numElems;

public:
    Stack();
    void push(T const &);
    void pop();
    T top() const;
    bool empty() const { return numElems == 0; }
    bool full() const { return numElems == MAXSIZE; }
};

template<typename T, int MAXSIZE>
Stack<T, MAXSIZE>::Stack() : numElems(0) {
    // 不做任何事情
}

template<typename T, int MAXSIZE>
void Stack<T, MAXSIZE>::push(T const &elem) {
    if (numElems == MAXSIZE) {
        throw std::out_of_range("Stack<>::push stack if full");
    }
    elems[numElems] = elem;
    ++numElems;
}

template<typename T, int MAXSIZE>
void Stack<T, MAXSIZE>::pop() {
    if (numElems <= 0) {
        throw std::out_of_range("Stack<>::pop() empty stack");
    }
    --numElems;
}

template<typename T, int MAXSIZE>
T Stack<T, MAXSIZE>::top() const {
    if (numElems <= 0) {
        throw std::out_of_range("Stack<>::top: empty stack");
    }
    return elems[numElems - 1];
} 
```

#### 非类型的函数模板参数

可以为函数模板定义非类型参数。例如：

```cpp
template<typename T, int VAL>
T addValue(T const &x) {
    return x + VAL;
}
```

#### 非类型模板参数的限制

非类型模板参数是有限制的，通常而言，它们可以是常整数（包括枚举值）或者指向外部链接对象的指针，浮点数和类对象是不允许作为非类型模板参数的。

> 注意：C++ 11 后浮点数可以作为非类型模板参数。

#### 小结

1. 模板可以具有值模板参数，而不仅仅是类型模板参数。
2. 对于非类型模板参数，你不能使用浮点数、class 类型的对象和内部链接对象（例如 string）作为实参。

### 技巧性基础知识

#### 关键字 typename

`typename` 指明模板内部的标识符可以是一个类型

例如：

```cpp
template <typename T>
class MyClass {
typename T::SubType * ptr;
};
```

上面程序中，第 2 个 `typename` 被用来说明：`SubType` 是定义于类 `T` 内部的一种类型。因此，`ptr` 是一个指向 `T::SubType` 类型的指针。

让我们来考虑一个 typename 的典型应用，即在模板代码中访问 STL 容器的迭代器：

```cpp
#include <iostream>

template<typename T>
void printcoll(T const &coll) {
    typename T::const_iterator pos;
    typename T::const_iterator end{coll.end};

    for (pos = coll.begin(); pos != end; ++pos) {
        std::cout << *pos << ' ';
    }
    std::cout << std::endl;
}
```

####  使用 `this->`

对于具有基类的类模板，自身使用名称 x 并不一定等同于`this->x`。即使该 x 是从基类继承获得的，也是如此。例如：

```cpp
template <typename T>
class Base {
public:
    void exit();
};

template <typename T>
class Derived : Base<T> {
public:
    void foo() {
        exit(); //调用外部的exit()或者出现错误
    }
};
```

你应该在它前面使用 `this->` 或者 `Base<T>::`.

#### 成员模板

类成员也可以是模板。

例如：对于 `Stack<>`，通过定义一个身为模板的赋值运算符：

```cpp
#include <deque>

template<typename T>
class Stack {
private:
    std::deque<T> elems;

public:
    void push(T const &);
    void pop();
    T top() const;
    bool empty() const { return elems.empty(); }

    template<typename T2>
    Stack<T> &operator=(Stack<T2> const &);
};

template<typename T>
template<typename T2>
Stack<T> &Stack<T>::operator=(Stack<T2> const &op2) {
    if ((void *)this == (void *)&op2) {
        return *this;
    }
    Stack<T2> tmp(op2);
    elems.clear();
    while (!tmp.empty()) {
        elems.push_front(tmp.top());
        tmp.pop();
    }
    return *this;
}
```

模板赋值运算符并没有取代缺省赋值运算符，对于相同类型栈之间的赋值，仍然会调用缺省赋值运算符。

#### 模板的模板参数

借助于模板的模板参数，可以只指定容器的类型而不需要指定所含元素的类型，就可以声明这个 Stack 类模板，为了获得这个特性，你必须把第 2 个模板参数指定为模板的模板参数：

```cpp
#include <deque>
#include <memory>

template<typename T,
         template<typename ELEM, typename ALLOC = std::allocator<ELEM>>
         class CONT = std::deque>
class Stack {
private:
    CONT<T> elems;

public:
    void push(T const &);
    void pop();
    T top() const;
    bool empty() const { return elems.empty(); }
};
```

#### 零初始化

对于 int、double 或者指针等基本类型，并不存在「用一个有用的缺省值来对它们进行初始化」的缺省构造函数；相反，任何未被初始化的局部变量都具有一个不确定（undefined）值。

所以应该显式地调用内建类型的缺省构造函数：

```cpp
template <typename T>
void foo() {
    T x = T();
}
```

对于类模板，在用某种类型实例化该模板后，为了确认它所有的
成员都已经初始化完毕，你需要定义一个缺省构造函数，通过一个初始化列表来初始化类模板的成员：

```cpp
template <typename T>
class MyClass {
private:
    T x;
public:
    MyClass(): x() {}
};
```

#### 使用字符串作为函数模板的实参

有时，把字符串传递给函数模板的引用参数会导致出人意料的运
行结果：

```cpp
#include <iostream>
#include <string>

template<typename T>
inline T const &max(T const &a, T const &b) {
    return a < b ? b : a;
}

int main(int arvc, char *argv[]) {

    std::string s;
    ::max("apple", "peach");
    // ::max("apple", "tomato");
    // ::max("apple", s);

    return 0;
}
```

问题在于：由于长度的区别，这些字符串属于不同的数组类型。
也就是说。

可以使用非引用参数：

```cpp
#include <iostream>
#include <string>

template<typename T>
inline T max(T a, T b) {
    return a < b ? b : a;
}

int main(int arvc, char *argv[]) {

    std::string a;
    ::max("apple", "peach");
    ::max("apple", "tomato");
    // ::max("apple", s);

    return 0;
}
```

产生这种调用结果的原因是：对于非引用类型的参数，在实参演绎的过程中，会出现数组到指针的类型转换。

#### 小结

1. 如果要访问依赖于模板参数的类型名称，你应该在类型名称前添加关键字 typename。
2. 嵌套类和成员函数也可以是模板。在本章的例子中，针对元素类型可以进行隐式类型转换的 2 个栈，我们实现了通用的赋值操作。然而，在这种情况下，类型检查依然是存在的。
3. 赋值运算符的模板版本并没有取代缺省赋值运算符。
4. 类模板也可以作为模板参数，我们称之为模板的模板参数。
5. 模板的模板实参必须精确地匹配。匹配时并不会考虑“模的模板实参”的缺省模板实参（如 std::deque 的 allocator）。
6. 通过显式调用缺省构造函数，可以确保模板的变量和成员都已经用一个缺省值完成初始化，这种方法对内建类型的变量和员也适用。
7. 对于字符串，在实参演绎过程中，当且仅当参数不是引用时，才会出现数组到指针的类型转换。



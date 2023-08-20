#include <iostream>
#include <gtest/gtest.h>
#include <list>
#include <string>
#include <string_view>
#include <utility>

template <typename... Types>
class MyVariadicTemplate1 {};

template <typename T1, typename... Types>
class MyVariadicTemplate2 {};

TEST(可变参数模板, 参数包) {
    MyVariadicTemplate1<int> instance1;
    MyVariadicTemplate1<std::string, double, std::list<int>> instance2;
    MyVariadicTemplate1<> instance3;
}

void handleValue(int value) {
    std::cout << "Integer: " << value << std::endl;
}

void handleValue(double value) {
    std::cout << "Double: " << value << std::endl;
}

void handleValue(std::string_view value) {
    std::cout << "String: " << value << std::endl;
}

void processValues() {}

template <typename T1, typename... Tn>
void processValues(T1 &&arg1, Tn &&...args) {
    handleValue(std::forward<T1>(arg1));
    processValues(std::forward<Tn>(args)...);
}

TEST(可变参数模板, 类型安全的变长参数列表) {
    processValues(1, 2, 3.56, "test", 1.1f);
}

class Mixin1 {
public:
    Mixin1(int i) : m_value { i } {};

    virtual void minxin1Func() {
        std::cout << "Mixin1: " << m_value << std::endl;
    }

private:
    int m_value;
};

class Mixin2 {
public:
    Mixin2(int i) : m_value { i } {};

    virtual void minxin2Func() {
        std::cout << "Mixin2: " << m_value << std::endl;
    }

private:
    int m_value;
};

template <typename... Mixins>
class MyClass : public Mixins... {
public:
    MyClass(Mixins const &...mixins) : Mixins { mixins }... {}

    virtual ~MyClass() = default;
};

TEST(可变参数模板, 可变数目的混入类) {

    MyClass<Mixin1, Mixin2> a { Mixin1 { 11 }, Mixin2 { 22 } };
    a.minxin1Func();
    a.minxin2Func();

    MyClass<Mixin1> b { Mixin1 { 33 } };
    b.minxin1Func();
    // b.minxin2Func(); // Error

    MyClass<> c;
    // c.minxin1Func(); // Error
    // c.minxin2Func(); // Error
}

template <typename... Tn>
void processValues1(Tn const &...args) {
    (handleValue(args), ...);
}

template <typename... Values>
void printValues(Values const &...values) {
    // ((std::cout << values << std::endl), ...);
    ((std::cout << values << " "), ...);
    std::cout << std::endl;
}

template <typename T, typename... Values>
double sumValues(T const &init, Values const &...values) {
    return (init + ... + values);
}

template <typename... Values>
double allTrue(Values const &...values) {
    return (... && values);
}

template <typename... Values>
double anyTrue(Values const &...values) {
    return (... || values);
}

TEST(可变参数模板, 折叠表达式) {
    /*
    |   名称  |        表达式        |含义
    |一元右折叠|    (pack op ...)    |
    |一元左折叠|    (... op pack)    |
    |二元右折叠|(pack op ... op Init)|
    |二元左折叠|(Init op ... op pack)|
    */
    // 长度为零的参数包允许一元折叠，但只能与 && || 和 , 结合使用
    printValues(1, "test", 2.34);

    std::cout << sumValues(1, 2, 3.3) << std::endl;
    std::cout << sumValues(1) << std::endl;

    std::cout << allTrue(1, 1, 0) << allTrue(1, 1) << allTrue() << std::endl; // 011
    std::cout << anyTrue(1, 1, 0) << anyTrue(0, 0) << anyTrue() << std::endl; // 100
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

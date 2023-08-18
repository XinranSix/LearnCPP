#include <array>
#include <format>
#include <functional>
#include <iostream>
#include <gtest/gtest.h>
#include <tuple>
#include <typeinfo>

TEST(元组, 简单使用) {
    using MyTuple = std::tuple<int, std::string, bool>;
    MyTuple t1 { 16, "Test", true };
    std::cout << std::format("t1 = ({} {} {})", std::get<0>(t1), std::get<1>(t1), std::get<2>(t1))
              << std::endl;

    std::cout << "Type of get<1>(t1) = " << typeid(get<1>(t1)).name() << std::endl;

    std::cout << "Type of element with index 2 = "
              << typeid(std::tuple_element<2, MyTuple>::type).name() << std::endl;

    std::cout << "Tuple Size = " << std::tuple_size<MyTuple>::value << std::endl;
    std::cout << "Tuple Size = " << std::tuple_size<decltype(t1)>::value << std::endl;

    using namespace std;

    std::tuple t2 { 16, "Test"s, true };

    double d { 3.14 };
    std::string str1 { "Test" };
    std::tuple t3 { 16, std::ref(d), std::cref(d), std::ref(str1) };

    std::cout << "d = " << d << std::endl;
    std::get<1>(t3) *= 2;
    std::cout << "d = " << d << std::endl;
}

TEST(元组, 分解元组之结构化绑定) {

    using namespace std;

    std::tuple t1 { 16, "Test"s, true };
    auto [i, str, b] { t1 };
    std::cout << std::format("Decomposed: i = {}, str = \"{}\", b = {}", i, str, b) << std::endl;

    auto &[i2, str2, b2] { t1 };
    i2 *= 2;
    str2 = "Hello World";
    b2 = !b2;
}

TEST(元组, 分解元组之tie) {
    std::tuple t1 { 16, "Test", true };
    int i { 0 };
    std::string str;
    bool b { false };
    std::cout << std::format("Before: i = {}, str = \"{}\", b = {}", i, str, b) << std::endl;
    // tie(i, str, b) = t1;
    tie(i, std::ignore, b) = t1;
    std::cout << std::format("After: i = {}, str = \"{}\", b = {}", i, str, b) << std::endl;
}

TEST(元组, 串联) {
    using namespace std;
    std::tuple t1 { 16, "Test"s, true };
    std::tuple t2 { 3.14, "string 2"s };
    auto t3 { std::tuple_cat(t1, t2) };
}

TEST(元组, 比较) {
    std::tuple t1 { 123, "def" };
    std::tuple t2 { 123, "abc" };
    if (t1 < t2) {
        std::cout << "t1 < t2" << std::endl;
    } else {
        std::cout << "t1 >= t2" << std::endl;
    }
}

class Foo {
public:
    Foo(int i, std::string s, bool b) : m_int { i }, m_str { std::move(s) }, m_bool { b } {}

    auto operator<=>(Foo const &rhs) {
        return std::tie(m_int, m_str, m_bool) <=> std::tie(rhs.m_int, rhs.m_str, rhs.m_bool);
    }

private:
    int m_int;
    std::string m_str;
    bool m_bool;
};

TEST(元组, 用元组实现类的比较) {
    Foo f1 { 42, "Hello", false };
    Foo f2 { 42, "World", false };
    std::cout << (f1 < f2) << std::endl;
    std::cout << (f2 > f1) << std::endl;
}

struct Foo1 {
public:
    Foo1(std::string str, int i) : m_str { std::move(str) }, m_int { i } {}

private:
    std::string m_str;
    int m_int;
};

TEST(元组, make_from_tuple) {
    std::tuple myTuple { "Helo world.", 42 };
    auto foo { std::make_from_tuple<Foo1>(myTuple) };
}

int add(int a, int b) {
    return a + b;
}

TEST(元组, apply) {
    std::cout << std::apply(add, std::tuple { 39, 3 }) << std::endl;
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

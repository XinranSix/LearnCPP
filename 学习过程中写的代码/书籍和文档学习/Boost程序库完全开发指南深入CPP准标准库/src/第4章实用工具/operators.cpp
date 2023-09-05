#include <algorithm>
#include <iostream>
#include <gtest/gtest.h>
#include <string>
#include <vector>
#include "boost/operators.hpp"
#include "fmt/core.h"
#include "boost/assign.hpp"
#include "boost/core/explicit_operator_bool.hpp"

class point : boost::less_than_comparable<point>,
              boost::equality_comparable<point> {
    // 只要重载 <，就能获得 <=，>=和>
    int x {}, y {}, z {};

public:
    explicit point(int a = 0, int b = 0, int c = 0)
        : x { a }, y { b }, z { c } {}

    void print() const { fmt::print("{}, {}, {}", x, y, z); }

    friend bool operator<(const point &l, const point &r) {
        return (l.x * l.x + l.y * l.y + l.z * l.z <
                r.x * r.x + r.y * r.y + r.z * r.z);
    }

    friend bool operator==(const point &l, const point &r) {
        return r.x == l.x && r.y == l.y && r.z == l.z;
    }
};

TEST(operators, 算术操作符1) {
    point p0, p1 { 1, 2, 3 }, p2 { 3, 0, 5 }, p3 { 3, 2, 1 };

    assert(p0 < p1 && p1 < p2);
    assert(p2 > p0);
    assert(p1 <= p3);
    assert(!(p1 < p3) && !(p1 > p3));

    p2 = p1;
    assert(p1 == p2);
    assert(p1 != p3);
}

class point1
    : boost::less_than_comparable<point1, boost::equality_comparable<point1>> {
    // 只要重载 <，就能获得 <=，>=和>
    int x {}, y {}, z {};

public:
    explicit point1(int a = 0, int b = 0, int c = 0)
        : x { a }, y { b }, z { c } {}

    void print() const { fmt::print("{}, {}, {}", x, y, z); }

    friend bool operator<(const point1 &l, const point1 &r) {
        return (l.x * l.x + l.y * l.y + l.z * l.z <
                r.x * r.x + r.y * r.y + r.z * r.z);
    }

    friend bool operator==(const point1 &l, const point1 &r) {
        return r.x == l.x && r.y == l.y && r.z == l.z;
    }
};

TEST(operators, 算术操作符2) {
    point1 p0, p1 { 1, 2, 3 }, p2 { 3, 0, 5 }, p3 { 3, 2, 1 };

    assert(p0 < p1 && p1 < p2);
    assert(p2 > p0);
    assert(p1 <= p3);
    assert(!(p1 < p3) && !(p1 > p3));

    p2 = p1;
    assert(p1 == p2);
    assert(p1 != p3);
}

/*
operators库提供的常用复合运算的概念如下。
■ totally_ordered：全序概念，组合了equality_comparable和less_than_comparable。
■ additive：可加减概念，组合了addable和subtractable。
■ multiplicative：可乘除概念，组合了multipliable和dividable。
■ arithmetic：算术运算概念，组合了additive和multiplicative。
■ unit_stoppable：可步进概念，组合了incrementable和decrementable
*/

class point2 : boost::totally_ordered<point2, boost::additive<point2>> {
    // 只要重载 <，就能获得 <=，>=和>
    int x {}, y {}, z {};

public:
    explicit point2(int a = 0, int b = 0, int c = 0)
        : x { a }, y { b }, z { c } {}

    void print() const { fmt::print("{}, {}, {}", x, y, z); }

    friend bool operator<(const point2 &l, const point2 &r) {
        return (l.x * l.x + l.y * l.y + l.z * l.z <
                r.x * r.x + r.y * r.y + r.z * r.z);
    }

    friend bool operator==(const point2 &l, const point2 &r) {
        return r.x == l.x && r.y == l.y && r.z == l.z;
    }

    point2 &operator+=(const point2 &r) {
        x += r.x;
        y += r.y;
        z += r.z;
        return *this;
    }

    point2 &operator-=(const point2 &r) {
        x -= r.x;
        y -= r.y;
        z -= r.z;
        return *this;
    }
};

TEST(operators, 复合运算概念) {
    point2 p0, p1 { 1, 2, 3 }, p2 { 5, 6, 7 }, p3 { 3, 2, 1 };

    using namespace boost::assign;
    std::vector<point2> v = (list_of(p0), p1, p2, p3);

    auto pos { std::find(begin(v), end(v), point2(1, 2, 3)) };

    pos->print();
    std::endl(std::cout);

    (p1 + p2).print();
    (p3 - p1).print();

    assert((p2 - p2) == p0);
}

TEST(operators, 相等与等价) {
    // 相等与等价是不一样的
    //  相等是指 p1 == p2
    // 等价是指 !(p1 < p2) && !(p1 > p2)
    /*
    operators库使用equality_comparable 和 equivalent
    明确地区分了相等与等价这两个概念。
    equality_comparable基于「==」，equivalent则基于「<」。
    但令人困扰的是它们最终都提供了操作符「==」，表现相同但含义不同。
    */
    point p0, p1 { 1, 2, 3 }, p2 { 5, 6, 7 }, p3 { 3, 2, 1 };
    using namespace boost::assign;

    std::vector<point> v = (list_of(p0), p1, p2, p3);

    auto pos { std::find(begin(v), end(v), point { 1, 2, 3 }) };
    for (; pos != v.end();
         pos = std::find(pos + 1, end(v), point { 1, 2, 3 })) {
        pos->print();
    }
    std::endl(std::cout);

    pos = std::find(begin(v), end(v), point { 2, 1, 3 });
    assert(pos == end(v));
}

template <typename T>
class my_smart_ptr : public boost::dereferenceable<my_smart_ptr<T>, T *> {
    T *p {};

public:
    my_smart_ptr(T *x) : p { x } {}
    ~my_smart_ptr() { delete p; }

    T &operator*() const { return *p; }
};

TEST(operators, 解引用操作符) {
    my_smart_ptr<std::string> p { new std::string { "123" } };
    assert(p->size() == 3);
}

template <typename T>
class my_smart_array : public boost::indexable<my_smart_array<T>, int, T &> {
    T *p {};

public:
    using this_type = my_smart_array<T>;
    using iter_type = T *;

    my_smart_array(T *x) : p { x } {}
    ~my_smart_array() { delete[] p; };

    friend iter_type operator+(const this_type &a, int n) { return a.p + n; }
};

TEST(operators, 下标操作符) {
    my_smart_array<double> ma { new double[10] };
    ma[0] = 1.0;
    *(ma + 1) = 2.0;
    std::cout << ma[1] << std::endl;
}

struct demo_a {
    BOOST_EXPLICIT_OPERATOR_BOOL()
    // operator bool() const { return true; }
    bool operator!() const { return false; }
};

struct demo_b {
    BOOST_EXPLICIT_OPERATOR_BOOL()
    // operator bool() const { return false; }
    bool operator!() const { return true; }
};

TEST(operators, 布尔转型操作符) {
    demo_a a {};
    demo_b b {};
    // assert(a != b);
    // assert(a > b); // 不允许隐式转换
}

TEST(operators, 二元操作符) {
    /*
    operators库提供了使用两个模板类型参数的概念类来支持这种用
    法，如 less_than_comparable＜T，U＞。对于不支持模板偏特化的编
    译器，operators 为每个操作符提供额外的两种形式，增加后缀“1”
    或“2”。如果程序可能在不同的编译器上编译，那么为了兼容请使用
    带扩展的模板
    */
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

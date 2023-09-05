#include <bits/types/FILE.h>
#include <cstdio>
#include <exception>
#include <iostream>
#include <gtest/gtest.h>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <utility>
#include <vector>
#include "boost/smart_ptr.hpp"
#include "boost/smart_ptr/make_shared_array.hpp"
#include "boost/smart_ptr/shared_ptr.hpp"
#include "boost/smart_ptr/owner_less.hpp"

TEST(shared_ptr, 操作函数) {
    boost::shared_ptr<int> spi { new int };
    assert(spi);
    *spi = 253;

    boost::shared_ptr<std::string> sps { new std::string { "smart" } };
    assert(sps->size() == 5);

    // boost::shared_ptr<int> dont_do_this { new int[10] }; // WARN: 不要这样子

    using sp_t = boost::shared_ptr<std::string>;
    std::map<sp_t, int> m;

    sp_t sp { new std::string { "one" } };
    m[sp] = 111;
}

TEST(shared_ptr, 基本用法) {
    boost::shared_ptr<int> sp { new int { 10 } };
    assert(sp.unique());

    boost::shared_ptr<int> sp2 = sp;

    assert(sp == sp2 && sp.use_count() == 2);

    *sp2 = 100;
    assert(*sp == 100);

    sp.reset();
    assert(!sp);
}

class shared {
private:
    boost::shared_ptr<int> p;

public:
    shared(boost::shared_ptr<int> p_) : p { p_ } {}

    void print() {
        std::cout << "count: " << p.use_count() << " v = " << *p << std::endl;
    }
};

void print_func(boost::shared_ptr<int> p) {
    std::cout << "count: " << p.use_count() << " v = " << *p << std::endl;
}

TEST(shared_ptr, 较复杂的用法) {
    boost::shared_ptr<int> p { new int { 100 } };
    shared s1 { p }, s2 { p };

    s1.print();
    s2.print();

    *p = 20;
    print_func(p);

    s1.print();
}

TEST(shared_ptr, 工厂函数) {
    auto sp { boost::make_shared<std::string>("make_shared") };
    auto spv { std::make_shared<std::vector<int>>(10, 2) };
    assert(spv->size() == 10);
}

TEST(shared_ptr, 应用于标准容器) {
    using vs = std::vector<boost::shared_ptr<int>>;
    vs v(10);

    int i { 0 };
    for (auto pos { begin(v) }; pos != end(v); ++pos) {
        (*pos) = boost::make_shared<int>(++i);
        std::cout << *(*pos) << ", ";
    }
    std::cout << std::endl;

    i = 0;
    for (auto &ptr : v) {
        ptr = boost::make_shared<int>(++i);
        std::cout << *ptr << ", ";
    }
}

class sample {
private:
    class impl;
    boost::shared_ptr<impl> p;

public:
    sample();
    void print();
};

class sample::impl {
public:
    void print() { std::cout << "impl print" << std::endl; }
};

sample::sample() : p { new impl } {}

void sample::print() { p->print(); }

TEST(shared_ptr, 应用于桥接模式) {
    sample s;
    s.print();
}

class abstract {
public:
    virtual void f() = 0;
    virtual void g() = 0;

protected:
    virtual ~abstract() = default;
};

class impl : public abstract {
public:
    impl() = default;
    virtual ~impl() = default;

public:
    virtual void f() override { std::cout << "class impl f" << std::endl; }
    virtual void g() override { std::cout << "class impl g" << std::endl; }
};

boost::shared_ptr<abstract> create() { return boost::make_shared<impl>(); }

TEST(shared_ptr, 应用于工厂模式) {
    auto p { create() };
    p->f();
    p->g();
}

class socket_t {};

socket_t *open_socket() {
    std::cout << "open_socket" << std::endl;
    return new socket_t {};
}

void close_socket(socket_t *s) { std::cout << "close_socket" << std::endl; }

TEST(shared_ptr, 定制删除器) {
    socket_t *s = open_socket();
    boost::shared_ptr<socket_t> p { s, close_socket };
    // boost::shared_ptr<socket_t> p { s, &close_socket }; // 与上面等价

    // boost::shared_ptr<FILE> fp { fopen("filename", "r"), fclose };
}

/*
C++标准（C++11.20.7.2）中定义了std::shared_ptr，功能与boost::shared_ptr基本相同，完全可以等价互换
*/

TEST(shared_ptr, 指针转型函数) {
    boost::shared_ptr<std::exception> sp1 { new std::bad_exception };

    auto sp2 { boost::dynamic_pointer_cast<std::bad_exception>(sp1) };
    auto sp3 { boost::static_pointer_cast<std::exception>(sp2) };

    assert(sp3 == sp1);
}

TEST(shared_ptr, 存储void) {
    /*
    shared_ptr<void>能够存储void*型指针，而void*型指针可以
    指向任意类型，因此shared_ptr<void>就像是一个泛型的指针容
    器，拥有容纳任意类型的能力。

    但将指针存储为void*型的同时会丧失原来的类型信息，为了在需
    要的时候正确使用指针，可以用static_pointer_cast<T>等转型函
    数将指针重新转为原来的指针。但这涉及运行时进行动态类型转换，
    会导致代码不够安全，建议最好不要这样使用
    */
}

void any_func(void *p) { std::cout << "some operate" << std::endl; }

TEST(shared_ptr, 删除器的高级用法) {
    /*
    基于 shared_ptr<void> 和定制删除器，shared_ptr可以有更
    “惊人”的用法。由于空指针可以是任何指针类型，因此利用 shared_ptr<void>
    还可以实现退出作用域时调用任意函数
    */
    boost::shared_ptr<void> p { nullptr, any_func };
}

TEST(shared_ptr, 别名构造函数) {
    auto p1 { boost::make_shared<std::pair<int, int>>(0, 1) };

    boost::shared_ptr<int> p2 { p1, &p1->second };
    assert(p1.use_count() == 2 && p1.use_count() == p2.use_count());

    assert((void *)p1.get() != (void *)p2.get());
    assert(&p1->second == p2.get());
}

TEST(shared_ptr, owner_less) {
    using int_ptr = boost::shared_ptr<int>;
    using int_ptr_less = boost::owner_less<int_ptr>;

    int_ptr p1 { new int { 10 } };
    int n = 20;
    int_ptr p2 { p1, &n };

    assert(!int_ptr_less()(p1, p2) && !int_ptr_less()(p2, p1));

    using int_set = std::set<int_ptr>;
    int_set s;

    s.insert(p1);
    s.insert(p2);
    assert(s.size() == 1);
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

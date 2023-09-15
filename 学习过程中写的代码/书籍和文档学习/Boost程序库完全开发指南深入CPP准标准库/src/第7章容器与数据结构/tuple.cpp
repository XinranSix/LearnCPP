#include <iostream>
#include <gtest/gtest.h>
#include <string>
#include <vector>
#include "boost/core/ref.hpp"
#include "boost/tuple/tuple.hpp"
#include "boost/tuple/tuple_comparison.hpp"
#include "boost/tuple/tuple_io.hpp"

using namespace boost;

TEST(tuple, 创建与赋值) {
    {
        using my_tuple = tuple<int, std::string>;
        using my_tuple2 = tuple<int, my_tuple>;
    }

    {
        using my_tuple = tuple<int, std::string, double>;
        my_tuple t1;
        my_tuple t2 { 1, "123" };
        my_tuple t3 { t1 };
        t2 = t3;

        int x;
        tuple<int &> t4 { x };
    }

    {
        using no_instance_t1 = tuple<void>; // 没有酱紫的 tuple 实例
        using no_instance_t2 = tuple<void>; // 没有酱紫的 tuple 实例

        tuple<void *> t1;          // OK
        tuple<double (*)(int)> t2; // OK
    }

    {
        make_tuple(2, 3.0);
        make_tuple(std::string {}, std::vector<int> {});
    };

    {
        int i {};
        std::string s;
        tuple<int, std::string &> t1 { boost::make_tuple(i, boost::ref(s)) };
        tuple<const int &, std::string &> t2 = { boost::make_tuple(
            boost::cref(i), boost::ref(s)) };
    }
}

TEST(tuple, 访问元素) {
    auto t { boost::make_tuple(1, "char[]", 100.0) };

    assert(t.get<0>() == 1);
    assert(t.get<2>() == 100.0);

    std::cout << t.get<1>() << std::endl;
    std::cout << ++t.get<2>() << std::endl;
}

TEST(tuple, 比较操作) {
    using my_tuple = boost::tuple<int, double, std::string>;

    my_tuple t1 { boost::make_tuple(1, 100.0, std::string { "abc" }) };
    my_tuple t2 { boost::make_tuple(1, 200.0, std::string { "def" }) };
    assert(t1 < t2);

    my_tuple t3 { t2 };
    assert(t2 == t3);
}

TEST(tuple, 输入输出) {
    using my_tuple = boost::tuple<int, double, std::string>;

    my_tuple t1 { 1, 2.0, "string" };
    std::cout << t1 << std::endl;

    std::cout << "please input tuple:";
    // std::cin >> t1;

    std::cout << t1 << std::endl;

    std::cout << boost::tuples::set_open('[') << boost::tuples::set_close(']');
    std::cout << boost::tuples::set_delimiter(',');
    std::cout << t1 << std::endl;
}

auto func() { return boost::make_tuple(1, 2.0, "string"); }

TEST(tuple, 联结变量) {

    int i {};
    double d {};
    std::string s;
    boost::tie(i, d, s) = func();
}

template <typename Tuple>
void print_tuple(const Tuple &t) {
    std::cout << t.get_head() << ", ";
    print_tuple(t.get_tail());
}

template <>
void print_tuple(const boost::tuples::null_type &) {}

TEST(tuple, 内部结构) {
    using t_type = boost::tuple<int, double, std::string>;
    t_type t { 1, 2.1, "string tuple" };
    print_tuple(t);
    std::endl(std::cout);
}

template <typename Visitor, typename Tuple>
typename Visitor::result_type visit_tuple(Visitor v, const Tuple &t) {
    v(t.get_head());
    return visit_tuple(v, t.get_tail());
};

struct print_visitor {
    typedef void result_type;
    template <typename T>
    result_type operator()(const T &t) {
        std::cout << t << ",";
    }
};

template <>
void visit_tuple //< print_visitor,  tuples::null_type>
    (print_visitor, const tuples::null_type &) {}

template <typename T>
struct max_visitor {
    T *tmp;
    max_visitor(T *t) : tmp { t } {}

    using result_type = void;
    result_type operator()(const T &t) { *tmp = *tmp < t ? t : *tmp; }
};

template <>
void visit_tuple(max_visitor<double>, const boost::tuples::null_type &) {}

TEST(tuple, 使用访问者模式) {
    boost::tuple<int, double, std::string> t(1, 2.1, "string visitor");
    visit_tuple(print_visitor(), t);

    {
        boost::tuple<int, long, float, double> t { 100, 5, 3.14, 314.15 };
        double *max_value = new double(t.get_head());

        max_visitor<double> mv(max_value);
        visit_tuple(mv, t);
        std::cout << *max_value << std::endl;
    }
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

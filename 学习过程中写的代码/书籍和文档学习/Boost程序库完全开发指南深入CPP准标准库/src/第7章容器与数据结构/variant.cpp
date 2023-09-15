#include <algorithm>
#include <cassert>
#include <iostream>
#include <gtest/gtest.h>
#include <iterator>
#include <string>
#include <vector>
#include "boost/variant.hpp"
#include "boost/variant/detail/apply_visitor_binary.hpp"
#include "boost/variant/detail/apply_visitor_delayed.hpp"
#include "boost/variant/get.hpp"
#include "boost/variant/static_visitor.hpp"
#include "boost/variant/variant.hpp"

TEST(variant, 访问元素) {
    boost::variant<int, float, std::string> v;
    v = "123";
    std::cout << v << std::endl;
}

TEST(variant, 用法) {
    using var_t = boost::variant<int, double, std::string>;

    var_t v { 1 };
    v = 2.13;
    var_t v2 { "string type" };
    v2 = v;

    assert(v.type() == typeid(double));

    std::cout << boost::get<double>(v) << std::endl;
    std::cout << boost::get<int>(var_t { 108 }) << std::endl;

    {
        var_t v;
        assert(v.type() == typeid(int));
        assert(v.which() == 0);

        v = "variant demo";
        std::cout << *get<std::string>(&v) << std::endl;

        try {
            std::cout << boost::get<double>(v) << std::endl;
        } catch (boost::bad_get &) { std::cout << "bad_get" << std::endl; }
    }
}

// using var_t = boost::variant<int, double>;

// void var_print(var_t &v) {
//     if (v.type() == typeid(int)) {
//         boost::get<int>(v) *= 2;
//         std::cout << v << std::endl;
//     } else if (v.type() == typeid(double)) {
//         boost::get<double>(v) *= 2;
//         std::cout << v << std::endl;
//     } else {
//         std::cout << "don't know type" << std::endl;
//     }
// }

struct var_print : public boost::static_visitor<> {
    template <typename T>
    void operator()(T &i) const {
        i *= 2;
        std::cout << i << std::endl;
    }

    void operator()(std::vector<int> &v) const {
        v.reserve(v.size() * 2);
        std::copy(begin(v), end(v), std::back_inserter(v));
        for (auto &x : v) {
            std::cout << x << ", ";
        }
        std::endl(std::cout);
    }
};

TEST(variant, 访问器) {
    using var_t = boost::variant<int, double, std::vector<int>>;

    var_t v { 1 };
    var_print vp;

    boost::apply_visitor(vp, v);
    v = 3.414;
    boost::apply_visitor(vp, v);

    v = std::vector<int> { 1, 2 };
    boost::apply_visitor(vp, v);

    auto vp2 { boost::apply_visitor(vp) };
    vp2(v);
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

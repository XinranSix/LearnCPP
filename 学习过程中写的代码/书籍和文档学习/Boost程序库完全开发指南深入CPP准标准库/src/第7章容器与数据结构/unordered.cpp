#include <complex>
#include <cstddef>
#include <iostream>
#include <gtest/gtest.h>
#include <string>
#include <tuple>
#include <utility>
#include "boost/assign/list_of.hpp"
#include "boost/unordered/detail/fwd.hpp"
#include "boost/unordered/unordered_map_fwd.hpp"
#include "boost/unordered/unordered_set_fwd.hpp"
#include "boost/unordered_set.hpp"
#include "boost/unordered_map.hpp"
#include "boost/assign.hpp"
#include "boost/functional/hash.hpp"

TEST(unordered, 散列集合的用法) {
    boost::unordered_set<int> s { 1, 2, 3, 4, 5 };

    for (auto x : s) {
        std::cout << x << " ";
    }
    std::endl(std::cout);
    std::cout << s.size() << std::endl;

    s.clear();
    std::cout << s.empty() << std::endl;

    s.insert(8);
    s.insert(45);
    std::cout << s.size() << std::endl;
    std::cout << *s.find(8) << std::endl;

    s.erase(45);

    using namespace boost::assign;
    boost::unordered_set<int> us1 = list_of(1)(2)(3);
    boost::unordered_set<int> us2 = list_of(3)(2)(1);
    assert(us1 == us2);
}

TEST(unordered, 散列集合_emplace) {
    using complex_t = std::complex<double>;
    boost::unordered_set<complex_t> s;

    s.emplace(1.0, 2.0);
    s.emplace(3.0, 4.0);

    for (auto &x : s) {
        std::cout << x << ", ";
    }
    std::endl(std::cout);

    s.emplace_hint(s.begin(), 5.0, 6.0);

    for (auto &x : s) {
        std::cout << x << ", ";
    }
    std::endl(std::cout);
}

TEST(unordered, 散列映射的用法) {
    using namespace boost::assign;

    boost::unordered_map<int, std::string> um =
        map_list_of(1, "one")(2, "two")(3, "three");

    um.insert(std::make_pair(10, "ten"));
    std::cout << um[10] << std::endl;
    um[11] = "eleven";
    um[15] = "fifteen";

    auto p { um.begin() };
    for (; p != um.end(); ++p) {
        std::cout << p->first << "-" << p->second << ", ";
    }
    std::endl(std::cout);

    um.erase(11);
    std::cout << um.size() << std::endl;

    boost::unordered_map<int, std::string> um1 = map_list_of(1, "11")(2, "22");
    boost::unordered_map<int, std::string> um2 =
        map_list_of(1, "one")(2, "two");
    assert(um1 != um2);
}

TEST(unordered, 散列映射_emplace) {
    using complex_t = std::complex<double>;
    using um_t = boost::unordered_map<int, complex_t>;
    um_t s;

    s.emplace(boost::unordered::piecewise_construct, std::make_tuple(1),
              std::make_tuple(1.0, 2.0));

    s.emplace(boost::unordered::piecewise_construct, std::make_tuple(3),
              std::make_tuple(3.0, 4.0));

    for (auto &x : s) {
        std::cout << x.first << "<->" << x.second << ", ";
    }

    s.emplace_hint(s.begin(), boost::unordered::piecewise_construct,
                   std::make_tuple(5), std::make_tuple(5.0, 6.0));
    for (auto &x : s) {
        std::cout << x.first << "<->" << x.second << ", ";
    }
    std::endl(std::cout);
}

TEST(unordered, 内部数据结构) {
    using namespace boost::assign;
    boost::unordered_set<int> us = (list_of(1), 2, 3, 4);

    for (size_t i { 0 }; i < us.bucket_count(); ++i) {
        std::cout << us.bucket_size(i) << ", ";
    }
    std::endl(std::cout);
}

struct demo_class {
    int a {};
    friend bool operator==(const demo_class &l, const demo_class &r) {
        return l.a == r.a;
    }
};

size_t hash_value(demo_class &s) { return boost::hash<int> {}(s.a); }

TEST(unordered, 支持自定义类型) { boost::unordered_set<demo_class> us; }

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

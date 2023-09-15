#include <boost/bimap/tags/tagged.hpp>
#include <iostream>
#include <gtest/gtest.h>
#include <string>
#include <utility>
#include "boost/assign/list_inserter.hpp"
#include "boost/assign/list_of.hpp"
#include "boost/bimap.hpp"
#include "boost/bimap/bimap.hpp"
#include <boost/bimap/multiset_of.hpp>
#include <boost/bimap/unordered_set_of.hpp>
#include <boost/bimap/unordered_multiset_of.hpp>
#include <boost/bimap/list_of.hpp>
#include <boost/bimap/vector_of.hpp>
#include <boost/bimap/unconstrained_set_of.hpp>
#include "boost/assign.hpp"
#include "boost/bimap/support/lambda.hpp"

TEST(bimap, 基本用法) {
    boost::bimap<int, std::string> bm;

    bm.left.insert(std::make_pair(1, "111"));
    bm.left.insert(std::make_pair(2, "222"));

    bm.right.insert(std::make_pair("string", 10));
    bm.right.insert(std::make_pair("bimap", 20));

    for (auto pos { bm.left.begin() }; pos != bm.left.end(); ++pos) {
        std::cout << "left[" << pos->first << "]=" << pos->second << std::endl;
    }

    {
        boost::bimap<int, std::string> bm;
        using vt = decltype(bm)::value_type;

        bm.insert(vt(3, "333"));
    }
}

TEST(bimap, 值的集合类型) {
    /*
    bimap定义的集合类型如下。
■ set_of：可以用作键值（索引），有序且唯一，相当于map。
■ multiset_of：可以用作键值（索引），有序，相当于multimap。
■ unordered_set_of：可以用作键值（索引），无序且唯一，相当于unordered_map。
■ unordered_multiset_of：可以用作键值（索引），无序，
其视图相当于unordered_multimap。
■ list_of：不能用作键值（索引），序列集合，无对应的标准容器。
■ vector_of：不能用作键值（索引），随机访问集合，无对应容器。
■ unconstrained_set_of：不能用作键值（索引），无任何约束关系，无对应容器。

在bimap的模板参数列表中使用这些集合类型，就可以任意定义bimap的映射关系；
如果不指定集合类型，bimap将默认使用set_of类型。
    */

    boost::bimap<int, boost::bimaps::unordered_set_of<std::string>> bm1;

    boost::bimap<boost::bimaps::multiset_of<int>,
                 boost::bimaps::multiset_of<std::string>>
        bm2;

    boost::bimap<boost::bimaps::unordered_set_of<int>,
                 boost::bimaps::list_of<std::string>>
        bm3;

    boost::bimap<boost::bimaps::vector_of<int>,
                 boost::bimaps::unconstrained_set_of<std::string>>
        bm4;
}

template <typename T>
void print_map(T &m) {
    for (auto &x : m) {
        std::cout << x.first << "<-->" << x.second << std::endl;
    }
}

TEST(bimap, 集合类型的用法) {
    boost::bimap<boost::bimaps::unordered_multiset_of<int>,
                 boost::bimaps::unordered_multiset_of<std::string>>
        bm;

    bm.left.insert(std::make_pair(1, "111"));
    bm.left.insert(std::make_pair(2, "222"));
    bm.left.insert(std::make_pair(2, "555"));

    bm.right.insert(std::make_pair("string", 10));
    bm.right.insert(std::make_pair("bimap", 20));
    bm.right.insert(std::make_pair("bimap", 2));

    print_map(bm.left);
}

TEST(bimap, 使用标签类型) {
    boost::bimap<boost::bimaps::tags::tagged<int, struct id>,
                 boost::bimaps::vector_of<std::string>>
        bm1;

    boost::bimap<
        boost::bimaps::multiset_of<boost::bimaps::tags::tagged<int, struct id>>,
        boost::bimaps::unordered_set_of<
            boost::bimaps::tags::tagged<std::string, struct name>>>
        bm2;

    boost::bimap<boost::bimaps::tagged<int, struct id>,
                 boost::bimaps::tagged<std::string, struct name>>
        bm;

    bm.by<id>().insert(std::make_pair(1, "samus"));
    bm.by<id>().insert(std::make_pair(2, "adam"));

    bm.by<name>().insert(std::make_pair("link", 10));
    bm.by<name>().insert(std::make_pair("zelda", 11));

    print_map(bm.by<name>());
}

TEST(bimap, 使用assign库) {
    using namespace boost::assign;

    using bm_t = boost::bimap<boost::bimaps::multiset_of<int>,
                              boost::bimaps::vector_of<std::string>>;

    bm_t bm = boost::assign::list_of<bm_t::relation>(1, "111")(2, "222");

    boost::assign::insert(bm.left)(3, "333")(4, "444");
    boost::assign::push_back(bm.right)("555", 5)("666", 6);
    print_map(bm.left);
}

TEST(bimap, 查找与替换) {
    using namespace boost::bimaps;
    using bm_t = bimap<int, std::string>;

    using namespace boost::assign;
    bm_t bm = boost::assign::list_of<bm_t::relation>(1, "mario")(2, "peach");

    auto pos { bm.left.find(1) };

    std::cout << "[" << pos->first << "]=" << pos->second << std::endl;

    auto pos2 { bm.right.find("peach") };
    std::cout << "[" << pos2->first << "]=" << pos2->second << std::endl;
}

TEST(bimap, 投射) {
    using namespace boost::bimaps;
    using bm_t = bimap<int, std::string>;

    using namespace boost::assign;
    bm_t bm = boost::assign::list_of<bm_t::relation>(1, "mario")(2, "peach");
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

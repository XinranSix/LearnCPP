#include <cstdlib>
#include <deque>
#include <forward_list>
#include <iostream>
#include <gtest/gtest.h>
#include <list>
#include <map>
#include <ostream>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <utility>
#include <vector>
#include "boost/assign.hpp"
#include "boost/assign/list_inserter.hpp"
#include "boost/assign/list_of.hpp"
#include "yj/tools/output_container.h"

using namespace boost::assign;

TEST(assign, operator_add_equal) {
    std::vector<int> v;
    v += 1, 2, 3, 4, 5, 6 * 6;

    std::set<std::string> s;
    s += "c", "cpp", "lua", "swift";

    std::map<int, std::string> m;
    m += std::make_pair(1, "one"), std::make_pair(2, "two");

    std::cout << v << std::endl;
    std::cout << s << std::endl;
    std::cout << m << std::endl;
}

TEST(assign, operator_小括号) {
    std::vector<int> v;
    push_back(v)(1)(2)(3)(4)(5);

    std::list<std::string> l;
    push_front(l)("c")("cpp")("lua")("swift");

    std::forward_list<std::string> fl;
    push_front(fl)("matrix")("reload");

    std::set<double> s;
    insert(s)(3.14)(0.618)(1.732);

    std::cout << v << std::endl;
    std::cout << l << std::endl;
    std::cout << fl << std::endl;
    std::cout << s << std::endl;

    {
        std::vector<int> v;
        push_back(v), 1, 2, 3, 4, 5;
        push_back(v)(6), 7, 64 / 8, (9), 10;

        std::deque<std::string> d;
        push_front(d)() = "breath", "of", "the", "wild";
        assert(d.size() == 5);

        std::cout << v << std::endl;
        std::cout << d << std::endl;
    }
}

TEST(assign, 初始化容器) {
    // assign库提供3个工厂函数
    // list_of（）、map_list_of（）/pair_list_of（）和tuple_list_of（），
    // 它们能够产生generic_list对象，我们就可以像使用list_inserter
    // 一样使用operator（）和operator，来填充数据。

    // list_of
    {
        std::cout << "list_of" << std::endl;
        std::vector<int> v = list_of(1)(2)(3)(4)(5);
        std::cout << v << std::endl;

        std::deque<std::string> d =
            (list_of("power")("bomb"), "phazon", "suit");
        std::cout << d << std::endl;

        std::set<int> a = (list_of(10), 20, 30, 40, 50);
        std::cout << a << std::endl;

        std::map<int, std::string> m =
            list_of(std::make_pair(1, "one"))(std::make_pair(2, "two"));
        std::cout << m << std::endl;
    }

    // map_list_of/pair_list_of
    {
        std::cout << "map_list_of / pair_list_of" << std::endl;

        std::map<int, int> m1 { map_list_of(1, 2)(3, 4)(5, 6) };
        std::cout << m1 << std::endl;

        std::map<int, std::string> m2 { map_list_of(1, "one")(2, "two") };
        std::cout << m2 << std::endl;
    }

    // tuple_list_of
    {
        std::cout << "tuple_list_of" << std::endl;

        // 🙄🙄🙄🙄🤣
    }
}

TEST(assign, 重复输入) {
    /*
    在填充数据时会遇到输入重复数据的问题，如果用之前的方法要
    写大量的重复代码，很麻烦，也容易造成多写或少写的错误。list_inserter 和
    generic_list 提供了成员函数repeat()、repeat_fun() 和range() 来减轻工作量
    */
    std::vector<int> v { list_of(1).repeat(3, 2)(3)(4)(5) };
    std::cout << v << std::endl;

    std::multiset<int> ms;
    insert(ms).repeat_fun(5, &rand).repeat(2, 1), 10;
    std::cout << ms << std::endl;

    std::deque<int> d;
    push_front(d).range(begin(v), begin(v) + 5);
    std::cout << d << std::endl;
}

TEST(assign, 操作非标准容器) {
    std::stack<int> stk = (list_of(1), 2, 3).to_adapter();
    stk += 4, 5, 6;
    for (; !stk.empty();) {
        std::cout << stk.top() << " ";
        stk.pop();
    }
    std::endl(std::cout);

    std::queue<std::string> q =
        (list_of("china")("us")("uk")).repeat(2, "russia").to_adapter();
    push(q)("germany");
    for (; !q.empty();) {
        std::cout << q.front() << " ";
        q.pop();
    }
    std::endl(std::cout);

    std::priority_queue<double> pq =
        (list_of(1.414), 1.732, 2.236).to_adapter();
    push(pq), 3.414, 2.71828;
    for (; !pq.empty();) {
        std::cout << pq.top() << " ";
        pq.pop();
    }
    std::endl(std::cout);
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

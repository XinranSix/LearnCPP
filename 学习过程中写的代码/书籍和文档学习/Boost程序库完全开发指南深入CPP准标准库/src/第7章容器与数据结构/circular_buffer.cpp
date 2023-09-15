#include <iostream>
#include <gtest/gtest.h>
#include "boost/assign/list_inserter.hpp"
#include "boost/assign/list_of.hpp"
#include "boost/circular_buffer.hpp"
#include "boost/circular_buffer/base.hpp"
#include "boost/assign.hpp"
#include "boost/circular_buffer/space_optimized.hpp"

using namespace boost;

TEST(circular_buffer, 用法) {
    circular_buffer<int> cb(5);
    assert(cb.empty());

    cb.push_back(1);
    cb.push_front(2);
    assert(cb.front() == 2);
    cb.insert(std::begin(cb), 3);

    for (auto pos { std::begin(cb) }; pos != std::end(cb); ++pos) {
        std::cout << *pos << ", ";
    }
    std::endl(std::cout);

    cb.pop_front();
    assert(cb.size() == 2);
    cb.push_back();
    assert(cb[0] == 2);

    using namespace boost::assign;
    circular_buffer<int> cb1 = (list_of(1), 2, 3);
    circular_buffer<int> cb2 = (list_of(3), 4, 5);
    circular_buffer<int> cb3 = cb1;

    assert(cb1 < cb2);
    assert(cb1 == cb3);
}

template <typename T>
void print(T &cb) {
    for (auto &x : cb) {
        std::cout << x << ", ";
    }
    std::endl(std::cout);
}

TEST(circular_buffer, 环形结构) {
    using namespace boost::assign;

    circular_buffer<int> cb = (list_of(1), 2, 3);
    print(cb);

    cb.push_back(4);
    print(cb);

    cb.push_back(5);
    print(cb);

    cb.pop_front();
    print(cb);

    circular_buffer<int> cb1 = (list_of(1), 2, 3, 4, 5);

    assert(cb1.full());
    print(cb1);

    int *p { cb1.linearize() };
    assert(p[0] == 1 && p[3] == 4);
    assert(cb1.is_linearized());

    cb1.rotate(cb1.begin() + 2);
    print(cb1);
}

TEST(circular_buffer, 空间优化) {
    circular_buffer_space_optimized<int> cb(10);
    boost::assign::push_back(cb)(1), 2, 3, 4;

    assert(cb.size() == 4);
    assert(cb.capacity() == 10);

    cb.resize(100, 10);
    assert(cb.size() == cb.capacity());
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

#include <algorithm>
#include <cassert>
#include <iostream>
#include <gtest/gtest.h>
#include <iterator>
#include <ostream>
#include <string>
#include "boost/array.hpp"
#include "boost/assign.hpp"
#include "boost/assign/list_inserter.hpp"
#include "boost/assign/list_of.hpp"

// NOTE: 用什么 boost::array, std::array 不香嘛

TEST(array, 用法) {
    boost::array<int, 10> arr;

    arr[0] = 1;
    arr.back() = 10;
    assert(arr[arr.max_size() - 1] == 10);

    arr.assign(777);
    for (auto &x : arr) {
        std::cout << x << ", ";
    }
    std::endl(std::cout);

    int *p { arr.c_array() };
    *(p + 5) = 253;
    std::cout << arr[5] << std::endl;

    arr.at(8) = 666;
    // std::sort(arr.begin(), arr.end());
    std::sort(std::begin(arr), std::end(arr));
    for (auto &x : arr) {
        std::cout << x << ", ";
    }
    std::endl(std::cout);
}

TEST(array, 初始化) {
    boost::array<std::string, 3> ar1 { "hyt1", "hyt2", "hyt3" };

    int a[10] = { 0 };
    boost::array<int, 10> ar = { 0 };
    assert(std::equal(std::begin(ar), std::end(ar), a));

    boost::array<std::string, 3> ar2 = { "racer" };
    assert(ar2.at(1).empty());

    using namespace boost::assign;
    boost::array<int, 3> arr(list_of(2)(4)(6));

    for (int i { 0 }; i < arr.size(); ++i) {
        std::cout << arr[i] << ", ";
    }
    std::endl(std::cout);
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

/*
array被收入C++标准后进行了一些修订，因此std::array（C++11.23.3.2）与boost：：array不完全相同。
    ■ std::array 接口使用noexcept关键字保证不抛出异常。
    ■ std::array 接口使用constexpr替代static保证函数在编译
    期优化。
    ■ std::array 没有c_array() 操作。
    ■ std::array 没有assign() 操作。
    ■ std::array 没有operator=赋值操作。
此外 std::array 还支持tuple操作，可以把 std::array 当作一个tuple，
执行 tuple_size<A>::value、tuple_element<I, A>::type等编译期元函数操作。
但总体来说， std::array 和boost::array的差别非常小，它们通常可以互换使用。
*/

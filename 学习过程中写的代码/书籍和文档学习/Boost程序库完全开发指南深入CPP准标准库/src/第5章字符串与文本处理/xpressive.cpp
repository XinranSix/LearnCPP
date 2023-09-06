#include <cassert>
#include <iostream>
#include <gtest/gtest.h>
#include "boost/xpressive/regex_algorithms.hpp"
#include "boost/xpressive/xpressive.hpp"
#include "boost/xpressive/xpressive_fwd.hpp"

/*
上述两种方式不是对立的，因为xpressive把它们融合成了一个整
体，两者可以在程序中以任意的形式组合混用。
■ 如果想混用两种方式或不关心这两种方式，
可以包含头文件"boost/xpressive/xpressive.hpp"。
■ 如果仅想使用静态方式，
可以只包含头文件"boost/xpressive/xpressive_static.hpp"。
■ 如果仅想使用动态方式，
可以只包含头文件"boost/xpressive/xpressive_dynamic.hpp"
*/

TEST(xpressive, 简单的正则匹配) {
    using namespace boost::xpressive;

    cregex reg { cregex::compile("a.c") };

    assert(regex_match("abc", reg));
    assert(regex_match("a+c", reg));
    assert(!regex_match("ac", reg));
    assert(!regex_match("abd", reg));
}

TEST(xpressive, 复杂的正则匹配) {}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

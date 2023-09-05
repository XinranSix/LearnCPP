#include <iostream>
#include <gtest/gtest.h>
#include "boost/logic/tribool.hpp"
#include "boost/logic/tribool_io.hpp"

/*
 不确定状态 indeterminate 是一个特殊的tribool 值，它与bool
 值的true 和false的运算遵循三态布尔逻辑。
     ■ 任何与indeterminate的比较操作结果都是indeterminate。
     ■ 在与indeterminate 的逻辑或运算（||）中，它只有与true
     的运算结果为true，其他均为indeterminate。
     ■ 在与indeterminate的逻辑与运算（&&）中，它只有与false的
     运算结果为false，其他均为indeterminate。
     ■ indeterminate的逻辑非操作（！）的结果仍为indeterminate。
     自由函数indeterminate()可以判断一个tribool是否处于不确定状态。
 */

TEST(tribool, 用法) {
    boost::tribool tb { true };
    boost::tribool tb2 { !tb };

    if (tb) {
        std::cout << "true" << std::endl;
    }

    tb2 = boost::indeterminate;
    assert(indeterminate(tb2));
    std::cout << tb2 << std::endl;

    if (tb2 == boost::indeterminate) {
        std::cout << "indeterminate" << std::endl;
    }

    if (boost::indeterminate(tb2)) {
        std::cout << "indeterminate" << std::endl;
    }

    std::cout << (tb2 || true) << std::endl;
    std::cout << (tb2 && false) << std::endl;
}

BOOST_TRIBOOL_THIRD_STATE(unknown)

TEST(tribool, 为第三态更名) {
    boost::tribool tb {unknown};
    assert(unknown(tb));
    assert(unknown(tb || false));
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

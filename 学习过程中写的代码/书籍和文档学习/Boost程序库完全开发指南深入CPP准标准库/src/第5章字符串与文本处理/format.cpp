#include <iostream>
#include <gtest/gtest.h>
#include "boost/format.hpp"
#include "boost/format/format_fwd.hpp"

TEST(format, 简单的例子) {
    std::cout << boost::format { "%s:%d+%d = %d\n" } % "sum" % 1 % 2 % (1 + 2);

    boost::format fmt { "(%1% + %2%) * %2% = %3%" };
    fmt % 2 % 5;
    fmt % ((2 + 5) * 5);
    std::cout << fmt.str() << std::endl;
}

TEST(format, 输入操作符) {
    
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

#include "boost/config/detail/suffix.hpp"
#include "boost/config/helper_macros.hpp"
#include <ios>
#include <iostream>
#include <gtest/gtest.h>
#include <string>

TEST(config, 编译期字符串化) {
    std::cout << BOOST_STRINGIZE(__LINE__) << " ";
    std::cout << std::boolalpha
              << (std::string { "10" } == BOOST_STRINGIZE(__LINE__)) << " ";

    int x = 255;
    std::cout << BOOST_STRINGIZE(x) << std::endl;
}

struct static_int {

    BOOST_STATIC_CONSTANT(int, v1 = 10);
    BOOST_STATIC_CONSTANT(int, v2 = 20);

    int a[v2];
};

TEST(config, 静态整型常量) {}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

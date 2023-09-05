#include <bitset>
#include <iostream>
#include <gtest/gtest.h>
#include <string>
#include "boost/utility.hpp"
#include "boost/utility/binary.hpp"
#include "boost/current_function.hpp"

TEST(utility, 二进制常量) {
    std::cout << BOOST_BINARY(0110) << std::endl;
    std::cout << BOOST_BINARY(0110 1101) << std::endl;
    std::cout << std::bitset<5> { BOOST_BINARY(0110) } << std::endl;

    std::cout << BOOST_BINARY_UL(101 1001) << std::endl;

    long long x { BOOST_BINARY_LL(1010) };
}

double func() {
    std::cout << BOOST_CURRENT_FUNCTION << std::endl;
    return 0.0;
}

std::string str { BOOST_CURRENT_FUNCTION };

TEST(utility, 调用函数名) {
    std::cout << str << std::endl;
    std::cout << __FUNCTION__ << std::endl;
    std::cout << BOOST_CURRENT_FUNCTION << std::endl;

    func();
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

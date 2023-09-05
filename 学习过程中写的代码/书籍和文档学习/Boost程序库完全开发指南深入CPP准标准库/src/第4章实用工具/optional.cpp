#include <cmath>
#include <iostream>
#include <gtest/gtest.h>
#include <string>
#include <vector>
#include "boost/none.hpp"
#include "boost/optional.hpp"
#include "boost/optional/optional.hpp"

TEST(optional, 用法1) {
    boost::optional<int> op0;
    boost::optional<int> op1 { boost::none };

    assert(!op0);
    assert(op0 == op1);

    assert(op1.value_or(25) == 25);
    std::cout << op1.value_or_eval([]() { return 874; }) << std::endl;

    boost::optional<std::string> ops { "test" };
    std::cout << *ops << std::endl;

    ops.emplace("monado", 3);
    assert(*ops == "mon");

    std::vector<int> v(10);
    boost::optional<std::vector<int> &> opv(v);
    assert(opv);
}

boost::optional<double> calc(int x) {
    return boost::optional<double> { x != 0, 1.0 / x };
}

boost::optional<double> sqrt_op(double x) {
    return boost::optional<double> { x >= 0, std::sqrt(x) };
}

TEST(optional, 用法2) {
    boost::optional<double> d = calc(10);

    if (d) {
        std::cout << *d << std::endl;
    }

    d = sqrt_op(-10);
    if (!d) {
        std::cout << "no result" << std::endl;
    }
}

TEST(optional, 工厂函数) {
    auto x { boost::make_optional(5) };
    assert(*x == 5);

    auto y { boost::make_optional<double>(*x > 10, 1.0) };
    assert(!y);
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

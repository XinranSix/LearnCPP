#include <exception>
#include <iostream>
#include <gtest/gtest.h>
#include <string>
#include "boost/exception/all.hpp"
#include "boost/exception/detail/error_info_impl.hpp"
#include "boost/exception/exception.hpp"
#include "boost/exception/get_error_info.hpp"

/*
boost.exception库针对标准库中异常类的缺陷进行了强化，提供
「<<」操作符重载，可以向异常传入任意数据，有助于增加异常的
信息和表达力，boost.exception库中的部分特性已经被收入C++标
准
*/

struct my_exception : virtual std::exception, boost::exception {};

TEST(exception, 向异常传递信息) {
    using err_no = boost::error_info<struct tag_err_no, int>;
    using err_str = boost::error_info<struct tag_err_str, std::string>;

    try {
        try {
            throw my_exception() << err_no(10);
        } catch (my_exception &e) {
            std::cout << *boost::get_error_info<err_no>(e) << std::endl;
            std::cout << e.what() << std::endl;
            e << err_str { "other info" };
            throw;
        }
    } catch (my_exception &e) {
        std::cout << *boost::get_error_info<err_str>(e) << std::endl;
    }
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

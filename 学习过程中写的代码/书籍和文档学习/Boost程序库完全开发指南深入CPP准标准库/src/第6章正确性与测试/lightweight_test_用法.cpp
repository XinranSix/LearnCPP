#include <iostream>
#include <stdexcept>
#include "boost/smart_ptr.hpp"
#include "boost/core/lightweight_test.hpp"
#include "boost/smart_ptr/make_shared_object.hpp"

/*
lightweight_test定义了数个测试断言，以下列出较常用的几个。
■ BOOST_TEST(e)：断言表达式成立。
■ BOOST_TEST_NOT(e)：断言表达式不成立。
■ BOOST_ERROR(s)：直接断言失败，输出错误消息s。
■ BOOST_TEST_EQ(e1，e2)：断言两个表达式相等。
■ BOOST_TEST_NE(e1，e2)：断言两个表达式不等。
■ BOOST_TEST_CSTR_EQ(e1，e2)：断言两个C字符串相等。
■ BOOST_TEST_CSTR_NE(e1，e2)：断言两个C字符串不相等。
■ BOOST_TEST_THROWS(e, ex)：断言表达式e抛出异常ex。
*/

int main(int argc, char *argv[]) {

    auto p { boost::make_shared<int>(10) };

    BOOST_TEST(*p == 10);
    BOOST_TEST(p.unique());
    BOOST_TEST_NOT(!p);

    BOOST_TEST_EQ(p.use_count(), 1);
    BOOST_TEST_NE(*p, 20);

    p.reset();
    BOOST_TEST(!p);

    BOOST_TEST_THROWS(*p, std::runtime_error);
    BOOST_ERROR("error accured!!");

    return boost::report_errors();
}

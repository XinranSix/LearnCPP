#include <iostream>
#include <gtest/gtest.h>
#include <string>
#include <vector>
#include "boost/any.hpp"
#include "boost/assign/list_of.hpp"
#include "boost/smart_ptr/shared_ptr.hpp"
#include "boost/assign.hpp"

TEST(any, 访问元素) {
    boost::any a { 10 };

    int n = boost::any_cast<int>(a);
    assert(n == 10);

    boost::any_cast<int &>(a) = 20;
    assert(boost::any_cast<int>(a) == 20);

    boost::any a1, a2 { 2.0 };
    assert(boost::any_cast<int *>(&a1) == nullptr);
    assert(boost::any_cast<std::string *>(&a2) == nullptr);
}

TEST(any, 用法) {
    boost::any a { 100 };

    a = std::string { "char*" };
    a = std::vector<std::vector<int>> {};

    a = std::string { "avatar" };

    std::cout << boost::any_cast<std::string>(a) << std::endl;
}

template <typename T>
bool can_cast(boost::any &a) {
    return typeid(T) == a.type();
}

template <typename T>
T &get(boost::any &a) {
    BOOST_ASSERT(can_cast<T>(a));
    return *boost::any_cast<T>(&a);
}

template <typename T>
T *get_pointer(boost::any &a) {
    return boost::any_cast<T>(&a);
}

TEST(any, 简化操作) {
    boost::any a;
    int x { 1 };
    a = x;
    assert(can_cast<int>(a));
    get<int>(a) = 10;
    *get_pointer<int>(a) = 20;
}

template <typename T>
boost::any make_ptr_any(T *p = 0) {
    return boost::any(boost::shared_ptr<T>(p));
}

template <typename T>
boost::shared_ptr<T> &get_shared(boost::any &a) {
    BOOST_ASSERT(can_cast<boost::shared_ptr<T>>(a));
    return *boost::any_cast<boost::shared_ptr<T>>(&a);
}

TEST(any, 保存指针) {
    boost::any a { make_ptr_any(new std::string { "long" }) };
    a = make_ptr_any<std::vector<int>>(new std::vector<int>);
}

TEST(any, 应用于容器) {
    std::vector<boost::any> v;

    v.push_back(10);
    v.push_back(1.414);
    v.push_back(boost::shared_ptr<int> { new int(100) });

    using namespace boost::assign;

    std::vector<boost::any> v2 =
        list_of<boost::any>(10)(0.618)(std::string { "char" });
    std::cout << v2.size() << std::endl;
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

#include <iostream>
#include <gtest/gtest.h>
#include <ostream>
#include <string>
#include "boost/lexical_cast.hpp"
#include "boost/lexical_cast/bad_lexical_cast.hpp"
#include "boost/lexical_cast/try_lexical_convert.hpp"

// using namespace boost;

TEST(lexical_cast, 用法) {
    int x { boost::lexical_cast<int>("100") };
    long y { boost::lexical_cast<long>("2000") };

    float pai { boost::lexical_cast<float>("3.14159e5") };
    double e { boost::lexical_cast<double>("2.71828") };
    double r { boost::lexical_cast<double>("1.414,x", 5) };

    std::cout << x << " " << y << " " << pai << " " << e << " " << r << " "
              << std::endl;

    std::string str { boost::lexical_cast<std::string>(456) };
    std::cout << str << std::endl;

    std::cout << boost::lexical_cast<std::string>(0.618) << std::endl;
    std::cout << boost::lexical_cast<std::string>(0x10) << std::endl;
}

template <typename T>
bool num_valid(const char *str) {
    T tmp {};
    return boost::conversion::try_lexical_convert(str, tmp);
}

TEST(lexical_cast, 错误处理) {
    try {
        std::cout << boost::lexical_cast<int>("0x100") << std::endl;
        std::cout << boost::lexical_cast<double>("HelloWorld") << std::endl;
        std::cout << boost::lexical_cast<long>("1000L") << std::endl;
    } catch (boost::bad_lexical_cast &e) {
        std::cout << "error: " << e.what() << std::endl;
    }

    int x {};
    assert(!boost::conversion::try_lexical_convert("0x1000", x));

    assert(num_valid<double>("3.14"));
    assert(!num_valid<int>("3.14"));
    assert(num_valid<int>("65535"));
}

TEST(lexical_cast, 转换要求) {
    /*
    ■ 转换起点对象是可流输出的，即定义了opreator<<。
    ■ 转换终点对象是可流输入的，即定义了opreator>>。
    ■ 转换终点对象必须是可默认构造、可拷贝构造的。
    */
}

template <typename T>
struct outable {
    friend std::ostream &operator<<(std::ostream &os, const T &x) {
        return os << typeid(T).name();
    }
};

class demo_class {
    friend std::ostream &operator<<(std::ostream &os, const demo_class &x) {
        return os << "demo_class'Name";
    }
};

TEST(lexical_cast, 转换自定义类) {}

TEST(lexical_cast, 对比标准) {
    assert(std::stoi(" 42 ") == 42);
    assert(std::stol("100L") == 100L);
    assert(std::stol("1000 9") == 1000L);
    assert(std::stod("3.14ispi") == 3.14);
    assert(std::to_string(776ul) == "776");
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

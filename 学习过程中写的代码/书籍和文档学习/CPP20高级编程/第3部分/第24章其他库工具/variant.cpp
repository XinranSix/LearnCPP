#include <iostream>
#include <gtest/gtest.h>
#include <string>
#include <tuple>
#include <variant>

class Foo {
public:
    Foo() = delete;
    Foo(int) {}
};

class Bar {
public:
    Bar() = delete;
    Bar(int) {}
};

TEST(variant, 使用) {
    std::variant<int, std::string, float> v;
    std::variant<int, int> v1; // 无效

    // std::variant<Foo, Bar> v2; // Error
    std::variant<std::monostate, Foo, Bar> v2;

    using namespace std;

    v = 12;
    std::cout << "Type index: " << v.index() << std::endl;
    v = 12.5f;
    std::cout << "Type index: " << v.index() << std::endl;
    v = "An std::sting"s;
    std::cout << "Type index: " << v.index() << std::endl;

    std::cout << "Contains an int: " << std::holds_alternative<int>(v) << std::endl;
    std::cout << "Contains an int: " << std::holds_alternative<string>(v) << std::endl;

    std::cout << std::get<string>(v) << std::endl;
    try {
        std::cout << std::get<0>(v) << std::endl;
    } catch (std::bad_variant_access const &ex) {
        std::cout << "Exception: " << ex.what() << std::endl;
    }

    std::string *theString { std::get_if<string>(&v) };
    int *theInt { std::get_if<int>(&v) };
    std::cout << "retrieved string: " << (theString ? *theString : "null") << std::endl;
    std::cout << "retrieved int: " << (theInt ? *theInt : 0) << std::endl;
}

class MyVisitor {
public:
    void operator()(int i) {
        std::cout << "int " << i << std::endl;
    }

    void operator()(std::string const &s) {
        std::cout << "string " << s << std::endl;
    }

    void operator()(float f) {
        std::cout << "float " << f << std::endl;
    }
};

TEST(variant, 将观察者模式应用于variant) {
    std::variant<int, std::string, float> v;

    using namespace std;

    v = 12;
    v = 12.5f;
    v = "An std::sting"s;

    std::visit(MyVisitor {}, v);
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

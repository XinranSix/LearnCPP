#include <bit>
#include <iostream>
#include <gtest/gtest.h>

struct Base {
    virtual ~Base() = default;
};

struct Derived : public Base {
    virtual ~Derived() = default;
};

TEST(类型转换, static_cast) {
    int i { 3 };
    int j { 4 };
    double result { static_cast<double>(i) / j };
    std::cout << result << std::endl;

    Base *b { nullptr };
    Derived *d { new Derived {} };
    b = d;
    // d = b; // Error
    d = static_cast<Derived *>(b);

    Base base;
    Derived derived;
    Base &br { derived };
    // Derived &dr { base }; // Error
    Derived &dr { static_cast<Derived &>(br) };

    // Base *b1 { new Base {} };
    // Derived *d1 { static_cast<Derived *>(b) }; // 不要这样做
}

class X {};
class Y {};

TEST(类型转换, reinterpret_cast) {
    X x;
    Y y;

    X *xp { &x };
    Y *yp { &y };

    xp = reinterpret_cast<X *>(yp);
    void *p { xp };
    xp = reinterpret_cast<X *>(p);

    X &xr { x };
    Y &yr { reinterpret_cast<Y &>(x) };
}

TEST(类型转换, std_bit_cast) {
    float asFloat { 1.23f };
    auto asUint { std::bit_cast<unsigned int>(asFloat) };
    if (std::bit_cast<float>(asUint) == asFloat) {
        std::cout << "Roundtrip success." << std::endl;
    }
}

class Base1 {
public:
    virtual ~Base1() = default;
};

class Derived1 : public Base1 {
    virtual ~Derived1() = default;
};

TEST(类型转换, dynamic_cast) {
    Base1 *b;
    Derived1 *d { new Derived1 {} };
    b = d;
    d = dynamic_cast<Derived1 *>(b);
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

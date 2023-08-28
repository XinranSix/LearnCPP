#include "fmt/core.h"
#include <functional>
#include <future>
#include <iostream>
#include <string>

struct X {
    void foo(int i, std::string const &str) {
        fmt::print("{} {}\n", i, str);
    }

    std::string bar(std::string const &str) {
        fmt::print("{}\n", str);
        return str;
    }
};

struct Y {
    double operator()(double value) {
        fmt::print("{}\n", value);
        return value;
    }
};

X baz(X &x) {
    fmt::print("baz()\n");
    return x;
}

class move_only {
public:
    move_only() {
        fmt::print("无参构造子\n");
    }

    move_only(move_only &&) {
        fmt::print("移动构造子\n");
    }

    move_only(move_only const &) = delete;

    move_only &operator=(move_only &&) {
        fmt::print("移动赋值运算符\n");
        return *this;
    }

    move_only &operator=(move_only const &) = delete;

    void operator()() {
        fmt::print("operator()\n");
    }
};

int main(int argc, char *argv[]) {

    X x;
    auto f1 { std::async(&X::foo, &x, 42, "hello") };
    auto f2 { std::async(&X::bar, x, "goodbye") };

    Y y;
    auto f3 { std::async(Y {}, 3.141) };
    auto f4 { std::async(std::ref(y), 2.718) };

    std::async(baz, std::ref(x));

    auto f5 { std::async(move_only {}) };

    return 0;
}

#include <iostream>
#include <string>
#include <utility>

const std::string message{"Test"};

const std::string &foo() { return message; }

int main(int arvc, char *argv[]) {

    auto x{123};

    auto f1(foo());
    auto &f2(foo());

    std::string str{"C++"};
    auto result{std::as_const(str)};

    int i{123};
    auto p{&i};
    auto *p1{&i};
    const auto p2{&i};
    auto const p3{&i};
    const auto *p4{&i};
    auto *const p5{&i};
    const auto *const p6{&i};

    return 0;
}

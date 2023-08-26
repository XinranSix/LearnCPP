#include "fmt/core.h"
#include <iostream>
#include <thread>

void func1() {
    fmt::print("func1()\n");
}

void func2(int i) {
    fmt::print("func2(): {}\n", i);
}

std::thread f() {
    return std::thread { func1 };
}

std::thread g() {
    std::thread t { func2, 42 };
    return t;
}

int main(int argc, char *argv[]) {
    return 0;
}

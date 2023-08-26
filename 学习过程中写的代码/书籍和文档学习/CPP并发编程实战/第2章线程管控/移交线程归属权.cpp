#include "fmt/core.h"
#include <iostream>
#include <thread>
#include <utility>

void f1() {
    fmt::print("f1()\n");
}

void f2() {
    fmt::print("f2()\n");
}

int main(int argc, char *argv[]) {

    std::thread t1 { f1 };
    std::thread t2 { std::move(t1) };

    t1 = std::thread { f2 };
    std::thread t3;
    t3 = std::move(t2);
    t1 = std::move(t3); // 此处不行，会丢弃掉 t1 原来所关联的线程

    return 0;
}

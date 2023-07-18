#include <vector>
#include <thread>
#include <cassert>
#include <iostream>
#include <algorithm>
#include <future>
#include <functional>
#include <condition_variable>

template<typename... Args>
void foo(Args... args) {}

int main() {
    int a[3][3];

    int(*p)[3] = a;

    return 0;
}

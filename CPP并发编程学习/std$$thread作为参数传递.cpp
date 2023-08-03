#include <iostream>
#include <thread>

void some_function() {}

void f(std::thread t) {}

void g() {
    f(std::thread(some_function));
    std::thread t(some_function);
    f(std::move(t));
    // f(t);
}

int main(int arvc, char *argv[]) { return 0; }

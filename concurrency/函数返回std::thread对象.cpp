#include <iostream>
#include <thread>

void some_function() {}
void some_other_function(int) {}

std::thread f() { return std::thread(some_function); }

std::thread g() {
    std::thread t(some_other_function, 42);
    return t;
}

int main(int arvc, char *argv[]) { return 0; }

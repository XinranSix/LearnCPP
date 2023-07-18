#include <iostream>
#include <thread>

void hello() { std::cout << "Hello Concurrent World\n"; }

int main() {
    std::thread t(hello); // 3
    t.join();             // 4
    return 0;
}
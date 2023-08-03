#include <iostream>
#include <thread>

void hello() { std::cout << "Hello Concurrent World\n"; }

int main(int arvc, char *argv[]) {

    std::thread t(hello);
    t.join();

    return 0;
}

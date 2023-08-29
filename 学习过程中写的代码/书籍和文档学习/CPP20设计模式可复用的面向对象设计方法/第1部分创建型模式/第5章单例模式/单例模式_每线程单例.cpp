#include "fmt/core.h"
#include <iostream>
#include <thread>

class PerThreadsSingleton {

    PerThreadsSingleton() { id = std::this_thread::get_id(); }

public:
    std::thread::id id;

    static PerThreadsSingleton &get() {
        thread_local PerThreadsSingleton instance;
        return instance;
    }
};

int main(int argc, char *argv[]) {

    std::thread t1 { [] {
        std::cout << "t1: " << PerThreadsSingleton::get().id << "\n";
    } };

    std::thread t2 { [] {
        std::cout << "t2: " << PerThreadsSingleton::get().id << "\n";
        std::cout << "t2 agein: " << PerThreadsSingleton::get().id << "\n";
    } };

    t1.join();
    t2.join();

    return 0;
}

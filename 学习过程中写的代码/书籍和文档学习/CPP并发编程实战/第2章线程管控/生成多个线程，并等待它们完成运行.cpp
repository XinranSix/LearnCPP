#include <iostream>
#include <thread>
#include <vector>

void do_work(unsigned id) {}

void f() {
    std::vector<std::thread> threads;
    for (unsigned i { 0 }; i < 20; ++i) {
        threads.emplace_back(do_work, i);
    }

    for (auto &entry : threads) {
        entry.join();
    }
}

int main(int argc, char *argv[]) {

    f();

    return 0;
}

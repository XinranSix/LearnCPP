#include <iostream>
#include <thread>

void do_something_in_current_thread() {}

struct func {
    int &i;
    func(int &i_) : i(i_) {}
    void operator()() {
        for (unsigned j = 0; j < 1000000; ++j) {
            std::cout << i << std::endl;
            i++;
        }
    }
};

void f() {
    int some_local_state = 0;
    func my_func(some_local_state);
    std::thread t(my_func);
    try {

    } catch (...) {
        t.join();
        throw;
    }
    t.join();
}

int main(int arvc, char *argv[]) {
    f();
    return 0;
}

#include <iostream>
#include <thread>

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

void oops() {
    int some_local_state = 0;
    func my_func(some_local_state);
    std::thread my_thread(my_func);
    my_thread.detach();
}

int main(int arvc, char *argv[]) {
    oops();
    return 0;
}

#include <iostream>
#include <thread>

void do_some_work() {}

void do_something() {}

void do_somthing_else() {}

class background_task {
public:
    void operator()() const {
        do_some_work();
        do_somthing_else();
    }
};

int main(int arvc, char *argv[]) {

    std::thread my_thread(do_some_work);

    background_task f;
    std::thread my_thread1(f);
    // std::thread my_thread2(background_task());
    std::thread my_thread3((background_task()));
    std::thread my_thread4{background_task()};

    std::thread my_thread5([]() {
        do_something();
        do_somthing_else();
    });

    return 0;
}

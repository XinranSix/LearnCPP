#include <iostream>
#include <thread>

void do_some_work() {}

class background_task {
public:
    void operator()() const {
        // do something
    }
};

int main(int argc, char *argv[]) {

    std::thread my_thread1 { do_some_work };

    background_task f;
    // NOTE: 这里 f 会被复制到新线程中
    std::thread my_thread2 { f };

    // std::thread my_thread3(background_task()); // Error: 被解释成函数声明
    std::thread my_thread4((background_task()));  // √
    std::thread my_thread5 { background_task() }; // √

    std::thread my_thread6([] {
        // do something
    });
    std::thread my_thread7 { [] {
        // do something
    } };

    return 0;
}

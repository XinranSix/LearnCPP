#include <cassert>
#include <iostream>
#include <thread>

void do_background_work() {}

int main(int arvc, char *argv[]) {

    std::thread t(do_background_work);
    t.detach();
    assert(!t.joinable());

    return 0;
}

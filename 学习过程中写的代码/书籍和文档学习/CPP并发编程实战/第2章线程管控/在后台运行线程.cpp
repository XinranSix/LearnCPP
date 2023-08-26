#include <cassert>
#include <iostream>
#include <thread>

int main(int argc, char *argv[]) {

    std::thread t { []() {} };
    t.detach();
    assert(t.joinable());

    return 0;
}

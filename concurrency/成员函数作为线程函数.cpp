#include <iostream>
#include <thread>
#include <functional>

struct X {
    void do_lengthy_work(int) {}
};

int main(int arvc, char *argv[]) {

    X my_x;
    int num{};

    std::thread t(&X::do_lengthy_work, &my_x, num);

    return 0;
}

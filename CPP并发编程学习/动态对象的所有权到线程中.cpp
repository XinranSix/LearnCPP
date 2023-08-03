#include <iostream>
#include <memory>
#include <thread>

struct big_object {
    void prepare_data(int num) {}
};

void process_big_object(big_object bg) {}

int main(int arvc, char *argv[]) {

    std::unique_ptr<big_object> p(new big_object);
    p->prepare_data(42);
    // std::thread t(process_big_object, std::move(p));

    return 0;
}

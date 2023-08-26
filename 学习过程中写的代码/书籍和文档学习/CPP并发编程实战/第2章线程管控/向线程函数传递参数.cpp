#include "fmt/core.h"
#include <iostream>
#include <string>
#include <thread>
#include <unistd.h>
#include <pthread.h>

void f(int i, std::string const &s) {
    fmt::print("{} {}\n", i, s);
}

using widget_id = unsigned long long;

struct widget_data {};

void update_data_for_widget(widget_id w, widget_data &data) {}

void oops_again(widget_id w) {
    widget_data data {};
    // std::thread t { update_data_for_widget, w, data }; // Error
    std::thread t { update_data_for_widget, w, std::ref(data) }; // Error
    t.join();
}

struct X {
    void f() {}
};

int main(int argc, char *argv[]) {

    // std::thread t { f, 3, "hello" }; // 不行
    std::thread t { f, 3, std::string { "hello" } }; // 不行
    t.join();

    oops_again(1);

    return 0;
}

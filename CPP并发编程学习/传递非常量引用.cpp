#include <iostream>
#include <thread>
#include <functional>

struct widget_id {};
struct widget_data {};

void update_data_widget(widget_id w, widget_data &data) {}

void display_status() {}

void process_widget_data(widget_data data) {}

void oops_again(widget_id w) {
    widget_data data;
    std::thread t(update_data_widget, w, std::ref(data));
    display_status();
    t.join();
    process_widget_data(data);
}

int main(int arvc, char *argv[]) {
    // oops_again();
    return 0;
}

#include <iostream>
#include <mutex>

std::mutex some_mutex;

std::unique_lock<std::mutex> get_lock() {
    std::unique_lock<std::mutex> lk { some_mutex };
    return lk;
}

void process_data() {
    std::unique_lock<std::mutex> lk { get_lock() };
    // do someting.
}

int main(int argc, char *argv[]) {
    return 0;
}

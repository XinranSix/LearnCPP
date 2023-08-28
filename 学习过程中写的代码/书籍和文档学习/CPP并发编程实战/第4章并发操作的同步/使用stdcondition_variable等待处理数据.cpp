#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>

class data_chunk {};

std::mutex mut;
std::queue<data_chunk> data_queue;
std::condition_variable data_cond;

void data_preparation_thread() {
    // while() {}
}

int main(int argc, char *argv[]) {
    return 0;
}

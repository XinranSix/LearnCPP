#include <chrono>
#include <cmath>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

static const int MAX = 10e8;
static double sum { 0 };

static std::mutex exclusive;

void concurrent_worker(int min, int max) {
    for (int i { min }; i <= max; ++i) {
        exclusive.lock();
        sum += std::sqrt(i);
        exclusive.unlock();
    }
}

void concurrent_task(int min, int max) {
    auto start_time { std::chrono::steady_clock::now() };

    unsigned concurrent_count { std::thread::hardware_concurrency() };
    std::cout << "hardware_concurrency: " << concurrent_count << std::endl;
    std::vector<std::thread> threads;
    min = 0;
    sum = 0;
    for (int t { 0 }; t < concurrent_count; ++t) {
        int range = max / concurrent_count * (t + 1);
        threads.push_back(std::thread { concurrent_worker, min, range });
        min = range + 1;
    }
    for (int i { 0 }; i < threads.size(); ++i) {
        threads[i].join();
    }

    auto end_time { std::chrono::steady_clock::now() };
    auto ms { std::chrono::duration_cast<std::chrono::milliseconds>(end_time -
                                                                    start_time)
                  .count() };
    std::cout << "Concurrent task finish, " << ms
              << " ms consumed, Result: " << sum << std::endl;
}

int main(int argc, char *argv[]) {

    concurrent_task(0, MAX);

    return 0;
}

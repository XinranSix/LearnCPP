#include <atomic>
#include <cstddef>
#include <format>
#include <iostream>
#include <gtest/gtest.h>
#include <mutex>
#include <syncstream>
#include <thread>
#include <threads.h>
#include <vector>

std::atomic_flag spinlock = ATOMIC_FLAG_INIT;

static const size_t NumberOfThreads { 50 };
static const size_t LoopsPerThread { 100 };

void doWork(size_t threadNumber, std::vector<size_t> &data) {
    for (size_t i { 0 }; i < LoopsPerThread; ++i) {
        while (spinlock.test_and_set()) {
        }
        data.push_back(threadNumber);
        spinlock.clear();
    }
}

TEST(互斥, 实现一个自旋锁) {
    std::vector<size_t> data;
    std::vector<std::thread> threads;
    for (size_t i { 0 }; i < NumberOfThreads; ++i) {
        threads.push_back(std::thread { doWork, i, std::ref(data) });
    }
    for (auto &t : threads) {
        t.join();
    }
    std::cout << std::format("data contains {} elements, expected {}.\n", data.size(),
                             NumberOfThreads * LoopsPerThread);
}

std::mutex mut1;
std::mutex mut2;

void process() {
    std::unique_lock lock1 { mut1, std::defer_lock };
    std::unique_lock lock2 { mut2, std::defer_lock };

    std::lock(lock1, lock2);
}

void process1() {
    std::scoped_lock locks { mut1, mut2 };
}

TEST(互斥, 一次获得多个锁) {
    process();
    process1();
}

std::once_flag g_onceFlag;

void initializeSharedResources() {
    std::cout << "Shared resources initialized." << std::endl;
}

void processingFunction() {
    std::call_once(g_onceFlag, initializeSharedResources);
    std::cout << "Processing" << std::endl;
}

TEST(互斥, call_once) {
    std::vector<std::thread> threads { 3 };
    for (auto &t : threads) {
        t = std::thread { processingFunction };
    }
    for (auto &t : threads) {
        t.join();
    }
}

struct Counter {
public:
    Counter(int id, int numIteration) : m_id { id }, m_numIterations { numIteration } {}

    void operator()() const {
        for (int i { 0 }; i < m_numIterations; ++i) {
            std::osyncstream { std::cout } << "Counter " << m_id << " has value " << i << std::endl;
        }
    }

private:
    int m_id;
    int m_numIterations;
};

TEST(互斥, 以线程安全方式写入流之同步流) {}

struct Counter1 {
public:
    Counter1(int id, int numIteration) : m_id { id }, m_numIterations { numIteration } {}

    void operator()() const {
        for (int i { 0 }; i < m_numIterations; ++i) {
            std::lock_guard lock { ms_mutex };
            std::cout << "Counter " << m_id << " has value " << i << std::endl;
        }
    }

private:
    int m_id;
    int m_numIterations;
    inline static std::mutex ms_mutex;
};

TEST(互斥, 以线程安全方式写入流之使用锁) {}

class Counter2 {
public:
    Counter2(int id, int numIteration) : m_id { id }, m_numIterations { numIteration } {}

    void operator()() const {
        for (int i { 0 }; i < m_numIterations; ++i) {
            using namespace std;
            std::unique_lock lock { ms_timedMutex, 200ms };
            if (lock) {
                std::cout << "Counter " << m_id << " has value " << i << std::endl;
            } else {
            }
        }
    }

private:
    int m_id;
    int m_numIterations;
    inline static std::timed_mutex ms_timedMutex;
};

TEST(互斥, 使用定时锁) {}

void initializeSharedResources1() {
    std::cout << "Shared resources initialized." << std::endl;
}

std::atomic<bool> g_initialized { false };
std::mutex g_mutex;

void processingFunction1() {
    if (!g_initialized) {
        std::unique_lock lock { g_mutex };
        if (!g_initialized) {
            initializeSharedResources1();
            g_initialized = true;
        }
    }
    std::cout << "OK" << std::endl;
}

TEST(互斥, 双重检查锁定) {
    std::vector<std::thread> threads;
    for (int i { 0 }; i < 5; ++i) {
        threads.push_back(std::thread { processingFunction1 });
    }
    for (auto &t : threads) {
        t.join();
    }
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

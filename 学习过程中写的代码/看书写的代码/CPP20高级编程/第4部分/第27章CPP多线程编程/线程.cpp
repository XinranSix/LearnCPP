#include <exception>
#include <format>
#include <functional>
#include <iostream>
#include <gtest/gtest.h>
#include <stdexcept>
#include <stop_token>
#include <thread>
#include <threads.h>

void counter(int id, int numIterations) {
    for (int i { 0 }; i < numIterations; ++i) {
        std::cout << "Counter " << id << " has value " << i << std::endl;
    }
}

TEST(线程, 通过函数指针创建线程) {
    std::thread t1 { counter, 1, 6 };
    std::thread t2 { counter, 2, 4 };
    t1.join();
    t2.join();
}

struct Counter {
public:
    Counter(int id, int numIterations) : m_id { id }, m_numIterations { numIterations } {}

    void operator()() const {
        for (int i { 0 }; i < m_numIterations; ++i) {
            std::cout << "Counter " << m_id << " has value " << i << std::endl;
        }
    }

private:
    int m_id;
    int m_numIterations;
};

TEST(线程, 通过函数对象创建线程) {
    std::thread t1 { Counter { 1, 20 } };

    Counter c { 2, 12 };
    // std::thread t2 { c};
    std::thread t2 { std::ref(c) };

    t1.join();
    t2.join();
}

TEST(线程, 通过lambad创建线程) {
    int id { 1 };
    int numIterations { 5 };
    std::thread t1 { [id, numIterations] {
        for (int i { 0 }; i < numIterations; ++i) {
            std::cout << "Counter " << id << " has value " << i << std::endl;
        }
    } };
    t1.join();
}

class Request {
public:
    Request(int id) : m_id { id } {}

    void process() {
        std::cout << "Processing request " << m_id << std::endl;
    }

private:
    int m_id;
};

TEST(线程, 通过成员函数创建线程) {
    Request req { 100 };
    std::thread t1 { &Request::process, &req };
    t1.join();
}

int k;
thread_local int n;

void threadFuntion(int id) {
    std::cout << std::format("Thread {}: k={}, n={}\n", id, k, n) << std::endl;
    ++n;
    ++k;
}

TEST(线程, 线程本地存储) {
    std::thread t1 { threadFuntion, 1 };
    t1.join();
    std::thread t2 { threadFuntion, 1 };
    t2.join();
}

TEST(线程, 取消线程) {}

TEST(线程, 自动join线程) {
    std::jthread job { [](std::stop_token token) {
        while (!token.stop_requested()) {
        }
    } };
}

TEST(线程, 从线程中获取结果) {}

void doSomeWork() {
    for (int i { 0 }; i < 5; ++i) {
        std::cout << i << std::endl;
    }
    std::cout << "Thread throwing a runtime_error exception..." << std::endl;
    throw std::runtime_error { "Exception from thread" };
}

void threadFunc(std::exception_ptr &err) {
    try {
        doSomeWork();
    } catch (...) {
        std::cout << "Thread caught exception, returing exception..." << std::endl;
        err = std::current_exception();
    }
}

void doWorkInThread() {
    std::exception_ptr error;
    std::thread t { threadFunc, std::ref(error) };
    t.join();
    if (error) {
        std::cout << "Main thread received exception, rethrowing it..." << std::endl;
        std::rethrow_exception(error);
    } else {
        std::cout << "Main thread did not receive any exception." << std::endl;
    }
}

TEST(线程, 复制和重新抛出异常) {
    try {
        doWorkInThread();
    } catch (std::exception const &e) {
        std::cout << "Main function caught: '" << e.what() << "'" << std::endl;
    }
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

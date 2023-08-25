#include <atomic>
#include <iostream>
#include <gtest/gtest.h>
#include <thread>
#include <type_traits>
#include <vector>

TEST(原子操作库, 使用原子类型1) {
    std::atomic<int> counter { 0 };
    ++counter;
}

class Foo {
private:
    int mArray[123];
};

class Bar {
private:
    int mInt;
};

TEST(原子操作库, is_trivially_copy) {
    std::atomic<Foo> f;
    // std::cout << std::is_trivially_copyable_v<Foo> << " " << f.is_lock_free() << std::endl;

    std::atomic<Bar> b;
    std::cout << std::is_trivially_copyable_v<Bar> << " " << b.is_lock_free() << std::endl;
}

TEST(原子操作库, 原子操作) {
    // fetch_add
    std::atomic<int> value { 10 };
    std::cout << "Value = " << value << std::endl;
    int fetched { value.fetch_add(4) };
    std::cout << "Fectched = " << fetched << std::endl;
    std::cout << "Value = " << value << std::endl;
}

TEST(原子操作库, 原子智能指针) {}

TEST(原子操作库, 原子引用) {}

void increment(std::atomic<int> &counter) {
    for (int i { 0 }; i < 100; ++i) {
        ++counter;
        using namespace std;
        std::this_thread::sleep_for(1ms);
    }
}

TEST(原子操作库, 使用原子类型2) {
    std::atomic<int> counter { 0 };
    std::vector<std::thread> threads;
    for (int i { 0 }; i < 10; ++i) {
        threads.push_back(std::thread { increment, std::ref(counter) });
    }

    for (auto &t : threads) {
        t.join();
    }
    std::cout << "Result = " << counter << std::endl;
}

TEST(原子操作库, 等待原子变量) {
    std::atomic<int> value { 0 };

    std::thread job { [&value] {
        std::cout << "Thread starts waiting" << std::endl;
        value.wait(0);
        std::cout << "Thread wakes up, value = " << value << std::endl;
    } };

    using namespace std;
    std::this_thread::sleep_for(2s);
    std::cout << "Main thread is going to change value to 1." << std::endl;
    value = 1;
    value.notify_all();

    job.join();
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

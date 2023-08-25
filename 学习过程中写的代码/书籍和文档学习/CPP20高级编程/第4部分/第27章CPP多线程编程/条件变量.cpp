#include <condition_variable>
#include <iostream>
#include <gtest/gtest.h>
#include <mutex>
#include <queue>
#include <string>

TEST(条件变量, 使用条件变量) {
    std::queue<std::string> m_queue;
    std::mutex m_mutex;

    std::condition_variable m_condVar;
    std::unique_lock lock { m_mutex };
    // m_queue.push()
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

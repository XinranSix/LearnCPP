#include <chrono>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <time.h>

TEST(时钟, clock) {
    std::chrono::time_point tpoint { std::chrono::system_clock::now() };

    time_t tt { std::chrono::system_clock::to_time_t(tpoint) };
    tm *t { localtime(&tt) };
    std::cout << std::put_time(t, "%H:%M:%S") << std::endl;
}

TEST(时钟, 将时间转成字符串) {
    std::chrono::time_point tpoint { std::chrono::system_clock::now() };

    time_t tt { std::chrono::system_clock::to_time_t(tpoint) };
    tm *t { localtime(&tt) };

    std::stringstream ss;
    ss << std::put_time(t, "%H:%M:%S");
    std::string stringTime { ss.str() };
    std::cout << stringTime << std::endl;

    char buffer[80] { 0 };
    strftime(buffer, sizeof(buffer), "%H:%M:%S", t);
    std::cout << buffer << std::endl;
}

TEST(时钟, high_resolution_clock) {
    // 计算代码消耗时间
    auto start { std::chrono::high_resolution_clock::now() };
    double d { 0 };
    for (int i { 0 }; i < 1'000'000; ++i) {
        d += std::sqrt(sin(i) * cos(i));
    }
    auto end { std::chrono::high_resolution_clock::now() };
    auto diff { end - start };
    std::cout << std::chrono::duration<double, std::milli> { diff }.count() << "ms" << std::endl;
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

#include <format>
#include <iostream>
#include <gtest/gtest.h>
#include <stdexcept>
#include <vector>
#include <string_view>
#include <fstream>

std::vector<int> readIntegerFile(std::string_view filename) {
    std::ifstream inputStream { filename.data() };
    if (!inputStream) {
        const std::string error { std::format("Unable to open file {}.",
                                              filename.data()) };
        throw std::invalid_argument { error };
    }

    std::vector<int> integers;
    int temp {};
    while (inputStream >> temp) {
        integers.push_back(temp);
    }

    if (!inputStream.eof()) {
        const std::string error { std::format("Unable to read file {}.",
                                              filename.data()) };
        throw std::runtime_error { error };
    }

    return integers;
}

TEST(异常与多态性, 在类层次结构中捕获异常) {
    // 一定要按引用捕获
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

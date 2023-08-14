#include <exception>
#include <format>
#include <iostream>
#include <gtest/gtest.h>
#include <stdexcept>
#include <string>
#include <vector>
#include <string_view>
#include <fstream>

double SafeDivide(double num, double den) {
    if (den == 0) {
        throw std::invalid_argument { "Divide by zero" };
    }
    return num / den;
}

TEST(异常机制, 抛出和捕获异常) {
    try {
        std::cout << SafeDivide(5, 2) << std::endl;
        std::cout << SafeDivide(10, 0) << std::endl;
    } catch (std::invalid_argument const &e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
}

std::vector<int> readIntegerFile(std::string_view filename) {
    std::ifstream inputStream { filename.data() };
    if (inputStream.fail()) {
        throw std::exception {};
    }

    std::vector<int> integers;
    int temp {};
    while (inputStream >> temp) {
        integers.push_back(temp);
    }
    return integers;
}

TEST(异常机制, 打开文件失败异常) {
    std::string const filename { "IntegerFile.txt" };
    std::vector<int> myInts;
    try {
        myInts = readIntegerFile(filename);
    } catch (std::exception const &e) {
        std::cerr << "Unable to open file " << filename << std::endl;
    }
    for (auto const &element : myInts) {
        std::cout << element << ' ';
    }
    std::cout << std::endl;
}

std::vector<int> readIntegerFile1(std::string_view filename) {
    std::ifstream inputStream { filename.data() };
    if (inputStream.fail()) {
        throw 5;
    }

    std::vector<int> integers;
    int temp {};
    while (inputStream >> temp) {
        integers.push_back(temp);
    }
    return integers;
}

TEST(异常机制, 异常类型1) {
    std::string const filename { "IntegerFile.txt" };
    std::vector<int> myInts;
    try {
        myInts = readIntegerFile1(filename);
    } catch (int e) {
        std::cout << std::format("Unable to open file {} (Error Code {})",
                                 filename, e)
                  << std::endl;
    }
    for (auto const &element : myInts) {
        std::cout << element << ' ';
    }
    std::cout << std::endl;
}

std::vector<int> readIntegerFile2(std::string_view filename) {
    std::ifstream inputStream { filename.data() };
    if (inputStream.fail()) {
        throw "Unable to open file";
    }

    std::vector<int> integers;
    int temp {};
    while (inputStream >> temp) {
        integers.push_back(temp);
    }
    return integers;
}

TEST(异常机制, 异常类型2) {
    std::string const filename { "IntegerFile.txt" };
    std::vector<int> myInts;
    try {
        myInts = readIntegerFile2(filename);
    } catch (const char *e) {
        std::cout << e << std::endl;
    }
    for (auto const &element : myInts) {
        std::cout << element << ' ';
    }
    std::cout << std::endl;
}

TEST(异常机制, 按const引用捕获异常对象) {
    // 建议按 const 引用捕获抛出的异常
    // 以防止在多态中出现的对象截断
}

std::vector<int> readIntegerFile3(std::string_view filename) {
    std::ifstream inputStream { filename.data() };
    if (inputStream.fail()) {
        throw std::runtime_error("Unable to open the file.");
    }

    std::vector<int> integers;
    int temp {};
    while (inputStream >> temp) {
        integers.push_back(temp);
    }

    if (!inputStream.eof()) {
        throw std::runtime_error("Error reading the file.");
    }

    return integers;
}

TEST(异常机制, 抛出并捕获多个异常) {
    std::string const filename { "IntegerFile.txt" };
    std::vector<int> myInts;
    try {
        myInts = readIntegerFile3(filename);
    } catch (std::exception const &e) {
        std::cout << e.what() << std::endl;
    }
    for (auto const &element : myInts) {
        std::cout << element << ' ';
    }
    std::cout << std::endl;
}

std::vector<int> readIntegerFile4(std::string_view filename) {
    std::ifstream inputStream { filename.data() };
    if (inputStream.fail()) {
        throw std::invalid_argument { "Unable to open the file." };
    }

    std::vector<int> integers;
    int temp {};
    while (inputStream >> temp) {
        integers.push_back(temp);
    }

    if (!inputStream.eof()) {
        throw std::runtime_error("Error reading the file.");
    }

    return integers;
}

TEST(异常机制, 抛出不同的异常) {
    std::string const filename { "IntegerFile.txt" };
    std::vector<int> myInts;
    try {
        myInts = readIntegerFile4(filename);
    } catch (std::invalid_argument const &e) {
        std::cout << e.what() << std::endl;
    } catch (std::runtime_error const &e) {
        std::cerr << e.what() << std::endl;
    }
    for (auto const &element : myInts) {
        std::cout << element << ' ';
    }
    std::cout << std::endl;
}

TEST(异常机制, 匹配和const) {
    // 增加 const 属性不会影响匹配的目的，例如下面的两种写法是一样的：
    // catch (std::runtime_error const& e)
    // catch (std::runtime_error &e)
}

TEST(异常机制, 匹配所有异常) {
    std::string const filename { "IntegerFile.txt" };
    std::vector<int> myInts;
    try {
        myInts = readIntegerFile4(filename);
    } catch (...) {
        std::cerr << "Error reading or opening file " << filename << std::endl;
    }
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

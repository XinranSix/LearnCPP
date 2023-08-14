#include <cstring>
#include <ctime>
#include <iomanip>
#include <ios>
#include <iostream>
#include <gtest/gtest.h>
#include <locale>
#include <string>
#include <format>

TEST(流式输出, 输出的基本概念) {
    int i { 7 };
    std::cout << i << std::endl;

    char ch { 'a' };
    std::cout << ch << std::endl;

    std::string myString { "Hello World." };
    std::cout << myString << std::endl;

    int j { 11 };
    std::cout << "The value of j is " << j << "!" << std::endl;

    std::cout << "Line 1" << std::endl
              << "Line 2" << std::endl
              << "Line 3" << std::endl;
}

TEST(流式输出, 输出流的方法) {
    const char *test { "hello there\n" };
    std::cout.write(test, strlen(test));
    std::cout.put('a');

    std::cout << "abc";
    std::cout.flush();
    std::cout << "def";
    std::cout << std::endl;
}

TEST(流式输出, 处理输出错误) {
    if (std::cout.good()) {
        std::cout << "All good" << std::endl;
    }

    std::cout.flush();
    // if (std::cout.fail()) {
    if (!std::cout) {
        std::cout << "Unable to flush to standard out" << std::endl;
    }
}

TEST(流式输出, 抛出异常) {
    std::cout.exceptions(std::ios::failbit | std::ios::badbit |
                         std::ios::eofbit);

    try {
        std::cout << "Hello World." << std::endl;
    } catch (std::ios_base::failure const &ex) {
        std::cerr << "Caught exception: " << ex.what()
                  << ", error code = " << ex.code() << std::endl;
    }

    std::cout.clear();
}

TEST(流式输出, 输出操作算子) {
    // Boolean values
    bool myBool { true };
    std::cout << "This is the default: " << myBool << std::endl;
    std::cout << "This is should be true: " << std::boolalpha << myBool
              << std::endl;
    std::cout << "This should be 1: " << std::noboolalpha << myBool
              << std::endl;

    // Simulate "%6d" with streams
    int i { 123 };
    printf("This should be '   123': %6d\n", i);
    std::cout << "This should be '   123': " << std::setw(6) << i << std::endl;

    // Simulate "%06d" with streams
    printf("This should be '000123': %06d\n", i);
    std::cout << "This should be '000123': " << std::setfill('0')
              << std::setw(6) << i << std::endl;

    // Fill with *
    std::cout << "This should be '***123': " << std::setfill('*')
              << std::setw(6) << i << std::endl;
    // Reset fill cgaracter
    std::cout << std::setfill(' ');

    // Floating point values
    double db1 { 1.452 };
    double db12 { 5 };
    std::cout << "This should be ' 5': " << std::setw(2) << std::noshowpoint
              << db12 << std::endl;
    std::cout << "This should be @@1.452: " << std::setw(7) << std::setfill('@')
              << db1 << std::endl;
    // Reset fill character
    std::cout << std::setfill(' ');

    // Instructs cout to start formatting numbers according to your location.
    // std::cout.imbue(std::locale { "zh_CN" });

    // Format numbers according to your location
    std::cout << "This is 1234567 formatted according to your location: "
              << 1234567 << std::endl;

    // Monetary value. What exactly a monetary value means depends on your
    // location
    std::cout << "This should be a monetary value of 120000, "
              << "formatted according to your location: "
              << std::put_money(120000) << std::endl;

    // Date and time
    time_t t_t { time(nullptr) };
    tm *t { localtime(&t_t) };
    std::cout << "This should be the current date and time "
              << "formatted according to your location: "
              << std::put_time(t, "%c") << std::endl;

    // Quoted string
    std::cout
        << "This should be: \"Quoted string with \\\"embedded quotes\\\".\": "
        << std::quoted("Quoted string with \"embedded quotes\".") << std::endl;

    std::cout << "This should be '1.2346': " << std::setprecision(5)
              << 1.23456789 << std::endl;

    std::cout.precision(5);
    std::cout << "This should be '1.2346': " << 1.23456789 << std::endl;
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

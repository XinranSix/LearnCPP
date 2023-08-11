#include <format>
#include <iostream>
#include <gtest/gtest.h>
#include <string>
#include <utility>
#include <vector>
#include "professional_cpp/spreadsheet.hpp"

void printSpreadsheet(Spreadsheet s) {};

TEST(对象中的动态内存分配, 浅复制的问题) {
    // Spreadsheet s1 { 4, 3 };
    // printSpreadsheet(s1);

    // Spreadsheet s2 { 2, 2 }, s3 { 4, 3 };
    // s2 = s3;
}

void helper(std::string &&message) {
}

void handleMessage(std::string &message) {
    std::cout << std::format("handlmessage with lvalue reference: {}", message)
              << std::endl;
}

void handleMessage(std::string &&message) {
    std::cout << std::format("handleMessage with rvalue reference: {}", message)
              << std::endl;

    // helper(std::move(message));
    // helper(std::forward<decltype(message)>(message));
}

TEST(对象中的动态内存分配, 右值和右值引用) {
    // a: lv a * 2： rv
    int q { 4 * 2 };

    std::string s1 { "Hello" };
    std::string s2 { " World" };
    handleMessage(s1);
    handleMessage(std::move(s1));
    handleMessage(s1 + s2);
    handleMessage("HYT");

    // int &i { 2 };// Error
    int a { 2 }, b { 3 };
    // int &j { a + b }; // Error

    int &&i1 { 2 };
    int a1 { 2 }, b1 { 3 };
    int &&j { a + b };
}

TEST(对象中的动态内存分配, stdexchange) {
    int a { 11 };
    int b { 22 };
    std::cout << std::format("Before exchange(): a = {}, b = {}", a, b)
              << std::endl;
    int returnedValue { std::exchange(a, b) };
    std::cout << std::format("After exchange(): a = {}, b = {}", a, b)
              << std::endl;
    std::cout << std::format("exchange() returned: {}", returnedValue)
              << std::endl;
}

Spreadsheet createObject() {
    return Spreadsheet { 3, 2 };
}

TEST(对象中的动态内存分配, 移动操作的测试) {
    std::vector<Spreadsheet> vec;
    for (size_t i { 0 }; i < 2; ++i) {
        std::cout << "Iteration " << i << std::endl;
        vec.push_back(Spreadsheet { 100, 100 });
        std::cout << std::endl;
    }
    Spreadsheet s { 2, 3 };
    s = createObject();

    Spreadsheet s2 { 5, 6 };
    s2 = s;
}

template <typename T>
void swapCopy(T &a, T &b) {
    T temp { a };
    a = b;
    b = temp;
}

template <typename T>
void swapMove(T &a, T &b) {
    T temp { std::move(a) };
    a = std::move(b);
    b = std::move(a);
}

class DataHolder {
public:
    // void setData(std::vector<int> const &data) {
    //     m_data = data;
    // }
    // void setData(std::vector<int> &&data) {
    //     m_data = std::move(data);
    // }
    void setData(std::vector<int> data) {
        m_data = std::move(data);
    }

private:
    std::vector<int> m_data;
};

TEST(对象中的动态内存分配, 向函数传递参数的最佳方法) {
    DataHolder wrapper;
    std::vector myData { 11, 22, 33 };
    wrapper.setData(myData);
    wrapper.setData({ 22, 33, 44 });
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

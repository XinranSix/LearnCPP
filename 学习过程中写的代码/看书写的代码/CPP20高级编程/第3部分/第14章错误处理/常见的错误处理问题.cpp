#include <cstddef>
#include <exception>
#include <format>
#include <iostream>
#include <gtest/gtest.h>
#include <limits>
#include <new>
#include <source_location>

TEST(常见的错误处理问题, 内存分配错误) {
    int *ptr { nullptr };
    size_t integerCount { std::numeric_limits<size_t>::max() };
    std::cout << std::format("Tring to allocate memory for {} integers.",
                             integerCount)
              << std::endl;

    try {
        ptr = new int[integerCount];
    } catch (std::bad_alloc const &e) {
        auto location { std::source_location::current() };
        std::cerr << std::format("{} ({}): Unable to allocate memory: {}",
                                 location.file_name(), location.line(),
                                 e.what())
                  << std::endl;
    }
}

TEST(常见的错误处理问题, 不抛出异常的new) {
    // size_t integerCount { std::numeric_limits<size_t>::max() };
    // int *ptr { new (std::nothrow) int[integerCount] };
    // if (ptr == nullptr) {
    //     auto location { std::source_location::current() };
    //     std::cerr << std::format("{}({}): Unable to allocate memory!",
    //                              location.file_name(), location.line())
    //               << std::endl;
    // }
}

class please_terminate_me : public std::bad_alloc {};

void myNewHandler() {
    std::cerr << "Unable to allocate memory." << std::endl;
    throw please_terminate_me {};
}

TEST(常见的错误处理问题, 定制内存分配失败的行为) {
#if 0
    try {
        std::new_handler oldHandler { std::set_new_handler(myNewHandler) };

        size_t numInts { std::numeric_limits<size_t>::max() };
        int *ptr { new int[numInts] };

        std::set_new_handler(oldHandler);

    } catch (please_terminate_me const &) {
        auto location { std::source_location::current() };
        std::cerr << std::format("{}({}): Terminating program.",
                                 location.file_name(), location.line())
                  << std::endl;
    }
#endif
}

template <typename T>
class Matrix {
public:
    Matrix(size_t width, size_t height);
    virtual ~Matrix();

private:
    void cleanup();

    size_t m_width { 0 };
    size_t m_height { 0 };
    T **m_matrix { nullptr };
};

template <typename T>
Matrix<T>::Matrix(size_t width, size_t height) {
    m_matrix = new T *[width] {};

    m_width = width;
    m_height = height;

    try {
        for (size_t i { 0 }; i < width; ++i) {
            m_matrix[i] = new T[height];
        }
    } catch (...) {
        std::cerr << "Exception caught in constructor, cleaning up..."
                  << std::endl;
        cleanup();
        std::throw_with_nested(std::bad_alloc {});
    }
}

template <typename T>
Matrix<T>::~Matrix() {
    cleanup();
}

template <typename T>
void Matrix<T>::cleanup() {
    for (size_t i { 0 }; i < m_width; ++i) {
        delete[] m_matrix[i];
    }
    delete[] m_matrix;
    m_matrix = nullptr;
    m_width = m_height = 0;
}

struct Element {
private:
    int m_value;
};

TEST(常见的错误处理问题, 构造函数中的错误) {
    Matrix<Element> m { 10, 10 };
}

class SubObject {
public:
    SubObject(int i) {
        throw std::runtime_error { "Exception by SubObject ctor" };
    }
};

class MyClass {
public:
    MyClass();

private:
    int *m_data { nullptr };
    SubObject m_subObject;
};

MyClass::MyClass() try : m_data{ new int[42]{ 1, 2, 3 }
}
, m_subObject { 42 } {}
catch (std::exception const &e) {
    delete[] m_data;
    m_data = nullptr;
    std::cout << std::format("function-try-block caught: '()'", e.what())
              << std::endl;
}

TEST(常见的错误处理问题, 构造函数的function_try_blocks) {
    try {
        MyClass m;
    } catch (std::exception const &e) {
        std::cout << std::format("main() caught: '{}'", e.what()) << std::endl;
    }
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

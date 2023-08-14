#include <exception>
#include <format>
#include <iostream>
#include <gtest/gtest.h>
#include <string_view>
#include <string>
#include <source_location>

void logMessage(std::string_view message, std::source_location const &location =
                                              std::source_location::current()) {
    std::cout << std::format("{}({}): {}: {}", location.file_name(),
                             location.line(), location.function_name(), message)
              << std::endl;
}

void foo() {
    logMessage("Starting execution of foo().");
}

TEST(源码位置, 日志记录的源码位置) {
    foo();
}

class MyException : public std::exception {
public:
    MyException(std::string message,
                std::source_location location = std::source_location::current())
        : m_message { std::move(message) }, m_location { std::move(location) } {
    }

    const char *what() const noexcept override {
        return m_message.c_str();
    };

    virtual const std::source_location &where() const noexcept {
        return m_location;
    }

private:
    std::string m_message;
    std::source_location m_location;
};

void doSomething() {
    throw MyException { "Throwing MyException" };
}

TEST(源码位置, 异常的源码位置) {
    try {
        doSomething();
    } catch (MyException const &e) {
        auto const &location { e.where() };
        std::cerr << std::format("Caught: '{}' at line in {}.", e.what(),
                                 location.line(), location.function_name())
                  << std::endl;
    }
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

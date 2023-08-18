#include <exception>
#include <format>
#include <iostream>
#include <stdexcept>
#include <string>

class MyException : public std::exception {
public:
    MyException(std::string message) : m_message { std::move(message) } {}

    const char *what() const noexcept override {
        return m_message.c_str();
    }

private:
    std::string m_message;
};

void doSomething() {
    try {
        throw std::runtime_error { "Throwing a runtime_error exceptionstd" };
    } catch (std::runtime_error const &e) {
        std::cout << std::format("{} caught a runtime_error", __func__)
                  << std::endl;
        std::cout << std::format("{} throwing MyException", __func__)
                  << std::endl;
        std::throw_with_nested(
            MyException { "MyException with nested runtime_error" });
    }
}

int main(int argc, char *argv[]) {

    try {
        doSomething();
    } catch (MyException const &e) {
        std::cout << std::format("{} caught MyException: {}", __func__,
                                 e.what())
                  << std::endl;
        auto const *nested { dynamic_cast<std::nested_exception const *>(&e) };

        try {
            std::rethrow_if_nested(e);
        } catch (std::runtime_error const &e) {
            std::cout << std::format(" Nested exception: {}", e.what())
                      << std::endl;
        }
    }

    return 0;
}

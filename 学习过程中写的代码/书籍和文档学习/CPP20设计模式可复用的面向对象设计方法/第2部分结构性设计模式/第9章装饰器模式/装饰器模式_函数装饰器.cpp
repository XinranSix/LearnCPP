#include <functional>
#include <iostream>
#include <string>

// MARK:🥰
struct Logger {
    std::function<void()> func;
    std::string name;

    Logger(std::function<void()> const &func, std::string const &name)
        : func { func }, name { name } {}

    void operator()() const {
        std::cout << "Entering " << name << "\n";
        func();
        std::cout << "Exiting " << name << "\n";
    }
};

template <typename Func>
struct Logger2 {
    Func func;
    std::string name;

    Logger2(Func const &func, std::string const &name)
        : func { func }, name { name } {}

    void operator()() const {
        std::cout << "Entering " << name << "\n";
        func();
        std::cout << "Exiting " << name << "\n";
    }
};

template <typename Func>
auto make_logger2(Func func, std::string const &name) {
    return Logger2<Func> { func, name };
}

template <typename>
struct Logger3;

template <typename R, typename... Args>
struct Logger3<R(Args...)> {
    Logger3(std::function<Args...> func, std::string const &name)
        : func { func }, name { name } {}

    R operator()(Args... args) {
        std::cout << "Entering " << name << std::endl;
        R result { func(args...) };
        std::cout << "Exiting " << name << std::endl;
        return result;
    }

    std::function<R(Args...)> func;
    std::string name;
};

template <typename R, typename... Args>
auto meke_logger3(R (*func)(Args...), std::string &name) {
    return Logger3<R(Args...)> { std::function<R(Args...)> { func }, name };
}

int main(int argc, char *argv[]) {

    Logger { []() {
                std::cout << "Hello"
                          << "\n";
            },
             "HelloFunction" }();

    auto call { make_logger2([]() { std::cout << "Hello!" << std::endl; },
                             "HelloFunction2") };
    call();

    return 0;
}

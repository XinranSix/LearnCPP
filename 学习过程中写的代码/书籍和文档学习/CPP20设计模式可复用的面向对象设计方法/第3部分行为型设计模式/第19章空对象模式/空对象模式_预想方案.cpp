#include <iostream>
#include <memory>
#include <string>
#include <utility>

struct Logger {
    virtual ~Logger() = default;
    virtual void info(std::string const &s) = 0;
    virtual void warn(std::string const &s) = 0;
};

class BankAccount {
    std::shared_ptr<Logger> log;

public:
    std::string name;
    int balance {};

    BankAccount(std::shared_ptr<Logger> const &logger, std::string name,
                int balance)
        : log { logger }, name { std::move(name) }, balance { balance } {}

    void deposit(int amount) {
        balance += amount;
        log->info("Deposited $" + std::to_string(amount) + " to " + name +
                  ", balance is now $" + std::to_string(balance));
    }
};

struct ConsoleLogger : Logger {

    virtual void info(std::string const &s) override {
        std::cout << "INFO: " << std::endl;
    }

    virtual void warn(std::string const &s) override {
        std::cout << "WARNING!!!" << s << std::endl;
    }
};

struct NullLogger final : Logger {

    virtual void info(std::string const &s) override {}

    virtual void warn(std::string const &s) override {}
};

int main(int argc, char *argv[]) { return 0; }

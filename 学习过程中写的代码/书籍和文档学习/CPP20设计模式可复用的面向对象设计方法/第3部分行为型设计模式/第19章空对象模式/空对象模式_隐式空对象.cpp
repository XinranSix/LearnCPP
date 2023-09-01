#include <iostream>
#include <memory>
#include <string>
#include <utility>

struct Logger {
    virtual ~Logger() = default;
    virtual void info(std::string const &s) = 0;
    virtual void warn(std::string const &s) = 0;
};

struct OptionalLogger : Logger {
    std::shared_ptr<Logger> impl;
    static std::shared_ptr<Logger> no_loggin;

    OptionalLogger(std::shared_ptr<Logger> const &logger) : impl { logger } {}

    virtual void info(std::string const &s) override {
        if (impl) {
            impl->info(s);
        }
    }

    virtual void warn(std::string const &s) override {
        if (impl) {
            impl->warn(s);
        }
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

class BankAccount {
    std::shared_ptr<OptionalLogger> logger;
    static std::shared_ptr<Logger> no_logging;

public:
    std::string name;
    int balance {};

    BankAccount(std::string name, int balance,
                std::shared_ptr<Logger> &logger = no_logging)
        : logger { std::make_shared<OptionalLogger>(logger) },
          name { std::move(name) }, balance { balance } {}

    void deposit(int amount) {
        balance += amount;
        logger->info("Deposited $" + std::to_string(amount) + " to " + name +
                     ", balance is now $" + std::to_string(balance));
    }
};

std::shared_ptr<Logger> BankAccount::no_logging {};

int main(int argc, char *argv[]) { return 0; }

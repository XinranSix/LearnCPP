#include <format>
#include <iostream>

struct BackAccount {
    int balance = 0;
    int overdraft_limit = -500;

    void deposit(int amount) {
        balance += amount;
        std::cout << std::format("deposited {}, balance is now {}.\n", amount,
                                 balance);
    }

    void withdraw(int amount) {
        if (balance - amount >= overdraft_limit) {
            balance -= amount;
            std::cout << std::format("withdraw {}, balance is now {}.\n",
                                     amount, balance);
        }
    }
};

struct Command {
    virtual void call() const = 0;
};

struct BackAccountCommand : Command {
    BackAccount &account;
    enum Action { deposit, withdraw } action;

    int amount;

    BackAccountCommand(BackAccount &account, Action const action,
                       int const amount)
        : account { account }, action { action }, amount { amount } {}

    virtual void call() const {
        switch (action) {
        case deposit:
            account.deposit(amount);
            break;
        case withdraw:
            account.withdraw(amount);
            break;
        }
    }
};

int main(int argc, char *argv[]) {

    BackAccount ba;

    BackAccountCommand cmd { ba, BackAccountCommand::deposit, 100 };

    cmd.call();

    return 0;
}

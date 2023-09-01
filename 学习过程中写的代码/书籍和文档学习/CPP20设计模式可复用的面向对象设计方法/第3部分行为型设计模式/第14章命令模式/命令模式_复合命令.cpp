#include <format>
#include <initializer_list>
#include <iostream>
#include <vector>

struct BackAccount {
    int balance = 0;
    int overdraft_limit = -500;

    void deposit(int amount) {
        balance += amount;
        std::cout << std::format("deposited {}, balance is now {}.\n", amount,
                                 balance);
    }

    bool withdraw(int amount) {
        if (balance - amount >= overdraft_limit) {
            balance -= amount;
            std::cout << std::format("withdrew {}, balance now {}.\n", amount,
                                     balance);
            return true;
        }
        return false;
    }
};

struct Command {
    virtual void call() = 0;
    virtual void undo() = 0;

    bool succeeded {};
};

struct BackAccountCommand : Command {
    BackAccount &account;
    enum Action { deposit, withdraw } action;

    int amount {};

    bool withdrawal_succeeded {};

    BackAccountCommand(BackAccount &account, Action const action,
                       int const amount)
        : account { account }, action { action }, amount { amount },
          withdrawal_succeeded { false } {}

    virtual void call() override {
        switch (action) {
        case deposit:
            account.deposit(amount);
            break;
        case withdraw:
            account.withdraw(amount);
            withdrawal_succeeded = account.withdraw(amount);
            break;
        }
    }

    virtual void undo() override {
        switch (action) {
        case withdraw:
            if (withdrawal_succeeded) {
                account.deposit(amount);
            }
            break;
        case deposit:
            account.withdraw(amount);
            break;
        }
    }
};

struct CompositeBankAccountCommand : std::vector<BackAccountCommand>, Command {
    CompositeBankAccountCommand(std::initializer_list<value_type> const &items)
        : std::vector<BackAccountCommand>(items) {}

    void call() override {

        bool ok = true;
        for (auto &cmd : *this) {
            if (ok) {
                cmd.call();
                ok = cmd.succeeded;
            } else {
                cmd.succeeded = false;
            }
        }
    }

    void undo() override {
        for (auto it { rbegin() }; it != rend(); ++it) {
            it->undo();
        }
    }
};

struct MoneyTransferCommand : CompositeBankAccountCommand {
    MoneyTransferCommand(BackAccount &from, BackAccount &to, int amount)
        : CompositeBankAccountCommand {
              BackAccountCommand { from, BackAccountCommand::withdraw, amount },
              BackAccountCommand { to, BackAccountCommand::deposit, amount }
          } {}
};

int main(int argc, char *argv[]) {

    BackAccount ba;

    BackAccountCommand cmd { ba, BackAccountCommand::deposit, 100 };

    cmd.call();

    return 0;
}

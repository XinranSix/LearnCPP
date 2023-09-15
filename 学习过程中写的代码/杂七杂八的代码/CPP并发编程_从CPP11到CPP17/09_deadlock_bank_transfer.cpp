#include <cstdlib>
#include <iostream>
#include <mutex>
#include <set>
#include <string>
#include <thread>
#include <utility>

class Account {
public:
    Account(std::string name, double money)
        : mName { std::move(name) }, mMoney { money } {}

public:
    void changeMoney(double amount) { mMoney += amount; }

    std::string getName() { return mName; }

    double getMoney() { return mMoney; }

    std::mutex *getLock() { return &mMoneyLock; }

private:
    std::string mName;
    double mMoney;
    std::mutex mMoneyLock;
};

class Bank {
public:
    void addAccount(Account *account) { mAccounts.insert(account); }

    bool transferMoney(Account *accountA, Account *accountB, double amount) {
        std::lock_guard guardA { *accountA->getLock() };
        std::lock_guard guardB { *accountB->getLock() };

        if (amount > accountA->getMoney()) {
            return false;
        }

        accountA->changeMoney(amount);
        accountB->changeMoney(amount);
        return true;
    }

    double totalMoney() const {
        double sum { 0 };
        for (auto a : mAccounts) {
            sum += a->getMoney();
        }
        return sum;
    }

private:
    std::set<Account *> mAccounts;
};

void randomTransfer(Bank *bank, Account *accountA, Account *accountB) {
    while (true) {
        double randomMoney { ((double)rand() / RAND_MAX) * 100 };
        if (bank->transferMoney(accountA, accountB, randomMoney)) {
            std::cout << "Tranfer " << randomMoney << " from "
                      << accountA->getName() << " to " << accountB->getName()
                      << ", Bank totalMoney: " << bank->totalMoney()
                      << std::endl;
        } else {
            std::cout << "Transfer failed, " << accountA->getName()
                      << " has only $" << accountA->getMoney() << ", but"
                      << randomMoney << " required" << std::endl;
        }
    }
}

int main(int argc, char *argv[]) {

    Account a { "Paul", 100 };
    Account b { "Moira", 100 };

    Bank aBank;
    aBank.addAccount(&a);
    aBank.addAccount(&b);

    std::thread t1 { randomTransfer, &aBank, &a, &b };
    std::thread t2 { randomTransfer, &aBank, &b, &a };

    t1.join();
    t2.join();

    return 0;
}

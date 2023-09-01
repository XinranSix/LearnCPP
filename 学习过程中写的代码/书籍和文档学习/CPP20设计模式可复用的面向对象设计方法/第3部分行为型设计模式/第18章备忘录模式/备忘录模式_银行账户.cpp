#include <iostream>
#include <format>
#include <ostream>

class Memento final {
    int balance {};

public:
    Memento(int balance) : balance { balance } {}

    friend class BackAccount;
};

struct BackAccount {
    int balance { 0 };

    explicit BackAccount(int balance) : balance { balance } {}

    Memento deposit(int amount) {
        balance += amount;
        return { balance };
    }

    void restore(Memento const &m) { balance = m.balance; }

    friend std::ostream &operator<<(std::ostream &os, BackAccount const &ba) {
        return os << std::format("Balance: {}", ba.balance);
    }
};

void memento() {
    BackAccount ba { 100 };
    auto m1 { ba.deposit(50) };
    auto m2 { ba.deposit(25) };
    std::cout << ba << std::endl;

    ba.restore(m1);
    std::cout << ba << std::endl;

    ba.restore(m2);
    std::cout << ba << std::endl;
}

int main(int argc, char *argv[]) {
    
    memento();

    return 0;
}

#include <format>
#include <initializer_list>
#include <map>
#include <set>
#include <iostream>
#include <gtest/gtest.h>
#include <stdexcept>
#include <string>
#include <utility>
#include "yj/tools/output_container.h"

TEST(有序关联容器, pair工具类) {
    std::pair<std::string, int> myPair { "hello", 5 };
    std::pair<std::string, int> myOtherPair;

    myOtherPair.first = "hello";
    myOtherPair.second = 6;

    std::pair<std::string, int> myThirdPair { myOtherPair };

    if (myPair < myOtherPair) {
        std::cout << "myPair is less than myOtherPair" << std::endl;
    } else {
        std::cout << "MyPair is greater than or equal to myOtherPair" << std::endl;
    }

    if (myOtherPair == myThirdPair) {
        std::cout << "myOtherPair is equal to myThirdPair" << std::endl;
    } else {
        std::cout << "myOtherPair is not equal to myThirdPair" << std::endl;
    }

    std::pair<int, double> aPair = std::make_pair(5, 10.10);
    auto pair2 { std::make_pair(5, 10.10) };
    std::pair pair3 { 5, 10.10 };
}

class Data final {
public:
    explicit Data(int value = 0) : m_value { value } {}

    int getValue() const {
        return m_value;
    }

    void setValue(int value) {
        m_value = value;
    }

private:
    int m_value;
};

TEST(有序关联容器, 构造map) {
    std::map<int, Data> dataMap;

    std::map<std::string, int> m1 { { "Marc G.", 123 },
                                    { "Warren B.", 456 },
                                    { "Peter V.W.", 789 } };

    std::map m2 { std::pair { "Marc G.", 123 }, std::pair { "Warren B.", 456 },
                  std::pair { "Peter V.W.", 789 } };
}

TEST(有序关联容器, map之插入元素) {
    std::map<int, Data> dataMap;

    auto ret { dataMap.insert({ 1, Data { 4 } }) };

    if (ret.second) {
        std::cout << "Insert succeeded" << std::endl;
    } else {
        std::cout << "Insert failed!" << std::endl;
    }

    ret = dataMap.insert(std::make_pair(1, Data { 6 }));
    if (ret.second) {
        std::cout << "Insert succeeded!" << std::endl;
    } else {
        std::cout << "Insert failed!" << std::endl;
    }

    if (auto result { dataMap.insert({ 1, Data { 4 } }) }; result.second) {
        std::cout << "Insert succeeded!" << std::endl;
    } else {
        std::cout << "Insert failed!" << std::endl;
    }

    if (auto [iter, success] { dataMap.insert({ 1, Data { 4 } }) }; success) {
        std::cout << "Insert succeeded!" << std::endl;
    } else {
        std::cout << "Insert failed!" << std::endl;
    }
}

TEST(有序关联容器, map之insert_or_assign方法) {
    std::map<int, Data> dataMap;

    auto ret { dataMap.insert_or_assign(1, Data { 7 }) };

    if (ret.second) {
        std::cout << "Inserted." << std::endl;
    } else {
        std::cout << "Overwritten." << std::endl;
    }

    ret = dataMap.insert_or_assign(1, Data { 9 });

    if (ret.second) {
        std::cout << "Inserted." << std::endl;
    } else {
        std::cout << "Overwritten." << std::endl;
    }
}

// void func(std::map<int, int> const &m) {
//     std::cout << m[1] << std::endl; // Error
// }

TEST(有序关联容器, map之中括号运算符) {
    std::map<int, Data> dataMap;

    dataMap[1] = Data { 4 };
    dataMap[1] = Data { 6 };
}

TEST(有序关联容器, map之emplace方法) {
    /*
    map 支持 emplace() 和 emplace_hint() 方法，用以原地构造
    还有一个 try_emplace() 方法，如果给定的键还不存在，那么它将在原位置插入元素，存在则什么也不做
    */
}

TEST(有序关联容器, map迭代器) {
    std::map<int, Data> dataMap;

    for (auto iter { cbegin(dataMap) }; iter != cend(dataMap); ++iter) {
        std::cout << iter->second.getValue() << std::endl;
    }

    for (auto const &p : dataMap) {
        std::cout << p.second.getValue() << std::endl;
    }

    for (auto const &[k, v] : dataMap) {
        std::cout << v.getValue() << std::endl;
    }
}

TEST(有序关联容器, map查找元素) {
    std::map<int, Data> dataMap;

    dataMap[1] = Data { 4 };
    dataMap[1] = Data { 6 };
    dataMap[1].setValue(100);

    auto it { dataMap.find(1) };
    if (it != end(dataMap)) {
        it->second.setValue(100);
    }

    auto isKeyInMap { dataMap.contains(1) };
}

TEST(有序关联容器, map删除元素) {
    std::map<int, Data> dataMap;
    dataMap[1] = Data { 4 };
    std::cout << std::format("There are {} elements with key 1.", dataMap.count(1)) << std::endl;
    dataMap.erase(1);
    std::cout << std::format("There are {} elements with ket 1.", dataMap.count(1)) << std::endl;
}

TEST(有序关联容器, map之节点) {
    std::map<int, Data> dataMap;
    dataMap[1] = Data { 4 };
    std::map<int, Data> dataMap2;

    // auto extractedNode { dataMap.extract(1) };
    // dataMap2.insert(std::move(extractedNode));

    dataMap2.insert(dataMap.extract(1));

    std::map<int, int> src { { 1, 11 }, { 2, 22 } };
    std::map<int, int> dst { { 2, 22 }, { 3, 33 }, { 4, 44 }, { 5, 55 } };
    dst.merge(src);
    std::cout << src << std::endl;
    std::cout << dst << std::endl;
}

class BankAccount final {
public:
    BankAccount(int accountNumber, std::string name)
        : m_accountNumber { accountNumber }, m_clientName { std::move(name) } {}

    void setAccountNumber(int accountNumber) {
        m_accountNumber = accountNumber;
    }

    int getAccountNumber() const {
        return m_accountNumber;
    }

    void setClientName(std::string name) {
        m_clientName = std::move(name);
    }

    std::string const &getClientName() const {
        return m_clientName;
    }

private:
    int m_accountNumber;
    std::string m_clientName;
};

class BankDB final {
public:
    bool addAccount(BankAccount const &account);

    void deleteAccount(int accountNumber);

    BankAccount &findAccount(int accountNumber);
    BankAccount &findAccount(std::string name);

    void mergeDatabase(BankDB &db);

private:
    std::map<int, BankAccount> m_accounts;
};

bool BankDB::addAccount(BankAccount const &account) {
    auto res { m_accounts.emplace(account.getAccountNumber(), account) };
    return res.second;
}

void BankDB::deleteAccount(int accountNumber) {
    m_accounts.erase(accountNumber);
}

BankAccount &BankDB::findAccount(int accountNumber) {
    auto it { m_accounts.find(accountNumber) };
    if (it == end(m_accounts)) {
        throw std::out_of_range("No account with that number.");
    }
    return it->second;
}

BankAccount &BankDB::findAccount(std::string name) {
    for (auto &[accountNumber, account] : m_accounts) {
        if (account.getClientName() == name) {
            return account;
        }
    }
    throw std::out_of_range { "No account with that name." };
}

void BankDB::mergeDatabase(BankDB &db) {
    m_accounts.merge(db.m_accounts);
    db.m_accounts.clear();
}

TEST(有序关联容器, map示例_银行账号) {
    BankDB db;
    db.addAccount(BankAccount { 100, "Nichloas Solter" });
    db.addAccount(BankAccount { 200, "Scott Kleper" });

    try {
        auto &acct { db.findAccount(100) };
        std::cout << "Found account 100" << std::endl;
        acct.setClientName("Nicholas A Solter");

        auto &acct2 { db.findAccount("Scott Kleper") };
        std::cout << "Found account of Scott Kleper" << std::endl;

        auto &acct3 { db.findAccount(1000) };
    } catch (std::out_of_range const &e) {
        std::cout << "Unable to find account: " << e.what() << std::endl;
    }
}

/* -------------------------------------------------------------------------- */

class BuddyList {
public:
    void addBuddy(std::string const &name, std::string const &buddy);
    void removeBuddy(std::string const &name, const std::string &buddy);
    bool isBuddy(std::string const &name, std::string const &buddy) const;
    std::vector<std::string> getBuddies(std::string const &name) const;

private:
    std::multimap<std::string, std::string> m_buddies;
};

void BuddyList::addBuddy(std::string const &name, std::string const &buddy) {
    if (!isBuddy(name, buddy)) {
        m_buddies.insert({ name, buddy });
    }
}

void BuddyList::removeBuddy(std::string const &name, const std::string &buddy) {
    auto begin { m_buddies.lower_bound(name) };
    auto end { m_buddies.upper_bound(name) };

    for (auto iter { begin }; iter != end; ++iter) {
        if (iter->second == buddy) {
            m_buddies.erase(iter);
            break;
        }
    }
}

bool BuddyList::isBuddy(std::string const &name, std::string const &buddy) const {
    auto [begin, end] { m_buddies.equal_range(name) };

    for (auto iter { begin }; iter != end; ++iter) {
        if (iter->second == buddy) {
            return true;
        }
    }
    return false;
}

std::vector<std::string> BuddyList::getBuddies(std::string const &name) const {
    auto [begin, end] { m_buddies.equal_range(name) };
    std::vector<std::string> buddies;
    for (auto iter { begin }; iter != end; ++iter) {
        buddies.push_back(iter->second);
    }
    return buddies;
}

TEST(有序关联容器, multimap示例_好友列表) {
    BuddyList buddies;
    buddies.addBuddy("Harry Potter", "Ron Weasley");
    buddies.addBuddy("Harry Potter", "Hermione Granger");
    buddies.addBuddy("Harry Potter", "Hagrid");
    buddies.addBuddy("Harry Potter", "Draco Malfoy");

    buddies.removeBuddy("Harry Potter", "Draco Malfoy");

    buddies.addBuddy("Hagrid", "Harry Potter");
    buddies.addBuddy("Hagrid", "Ron Weasley");
    buddies.addBuddy("Hagrid", "Hermione Granger");

    auto harrysFriends { buddies.getBuddies("Harry Potter") };

    std::cout << "Harry's friends" << std::endl;
    for (auto const &name : harrysFriends) {
        std::cout << "\t" << name << std::endl;
    }
}

/* -------------------------------------------------------------------------- */

class AccessList final {
public:
    AccessList() = default;

    AccessList(std::initializer_list<std::string> users) {
        m_allowed.insert(begin(users), end(users));
    }

    void addUser(std::string user) {
        m_allowed.emplace(user);
    }

    void removeUser(const std::string &user) {
        m_allowed.erase(std::string(user));
    }

    bool isAllowed(const std::string &user) const {
        return (m_allowed.count(user) != 0);
    }

    std::vector<std::string> getAllUsers() const {
        return { begin(m_allowed), end(m_allowed) };
    }

private:
    std::set<std::string> m_allowed;
};

TEST(有序关联容器, set示例_访问控制列表) {
    AccessList fileX { "maregoire", "baduser" };
    fileX.addUser("pvw");
    fileX.removeUser("baduser");

    if (fileX.isAllowed("maregoire")) {
        std::cout << "maregoire has permissions" << std::endl;
    }

    if (fileX.isAllowed("baduser")) {
        std::cout << "baduser has permissions" << std::endl;
    }

    auto users { fileX.getAllUsers() };
    for (auto const &user : users) {
        std::cout << user << " ";
    }
    std::cout << std::endl;
}

TEST(有序关联容器, multiset) {
    /*
    multiset 之于 set，相当于 multimap 之于 map
    */
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

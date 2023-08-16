#include <map>
#include <set>
#include <iostream>
#include <gtest/gtest.h>
#include <string>
#include <utility>

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

TEST(有序关联容器, map查找元素) {}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

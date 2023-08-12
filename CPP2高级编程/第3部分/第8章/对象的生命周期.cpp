#include <iostream>
#include <gtest/gtest.h>
#include <memory>
#include <stdexcept>
#include <string>
#include "professional_cpp/spreadsheetCell.hpp"
#include <initializer_list>
#include <vector>

TEST(对象的生命周期, 创建对象) {
    class MyClass {
    private:
        std::string m_name;
    };

    MyClass obj;

    int x { 0 };
}

TEST(对象的生命周期, 构造函数) {
    class MyClass {
    private:
        std::string m_name;
    };

    MyClass obj;

    int x { 0 };
}

TEST(对象的生命周期, 在栈中使用构造函数) {
    // SpreadsheetCell myCell(5), anotherCell(4);
    SpreadsheetCell myCell { 5 }, anotherCell { 4 };
    std::cout << "cell 1: " << myCell.getValue() << std::endl;
    std::cout << "cell 2: " << anotherCell.getValue() << std::endl;
}

TEST(对象的生命周期, 在自由存储区中使用构造函数) {
    auto smartCellp { std::make_unique<SpreadsheetCell>(4) };
    SpreadsheetCell *myCellp { new SpreadsheetCell { 5 } };
    SpreadsheetCell *anotherCellp { nullptr };
    anotherCellp = new SpreadsheetCell { 4 };

    delete myCellp;
    myCellp = nullptr;
    delete anotherCellp;
    anotherCellp = nullptr;
}

TEST(对象的生命周期, 另外一个构造函数) {
    SpreadsheetCell aThirdCell { "test" };
    SpreadsheetCell aFourthCell { 4.4 };
    auto aFifthCellp { std::make_unique<SpreadsheetCell>("5.5") };

    std::cout << "aThirdCell: " << aThirdCell.getValue() << std::endl;
    std::cout << "aFourthCell: " << aFourthCell.getValue() << std::endl;
    std::cout << "aFifthCell: " << aFifthCellp->getValue() << std::endl;
}

TEST(对象的生命周期, 默认构造器) {
    SpreadsheetCell cells[3];
    SpreadsheetCell *myCellp { new SpreadsheetCell[10] };

    SpreadsheetCell cells1[3] { SpreadsheetCell { 0 }, SpreadsheetCell { 23 },
                                SpreadsheetCell { 41 } };

    SpreadsheetCell myCell;
    myCell.setValue(6);
    std::cout << "cell 1: " << myCell.getValue() << std::endl;

    auto smartCellp { std::make_unique<SpreadsheetCell>() };
    SpreadsheetCell *myCellp1 { new SpreadsheetCell {} };

    SpreadsheetCell *myCellp2 { new SpreadsheetCell };
    SpreadsheetCell *myCellp3 { new SpreadsheetCell() };

    delete myCellp1;
    myCellp1 = nullptr;
    delete myCellp2;
    myCellp2 = nullptr;
    delete myCellp3;
    myCellp3 = nullptr;
}

class Foo {
public:
    Foo(double value);

private:
    double m_value { 0 };
};

Foo::Foo(double value) : m_value { value } {
    std::cout << "Foo::m_value = " << m_value << std::endl;
}

class MyClass {
public:
    MyClass(double value);

private:
    double m_value;
    Foo m_foo;
};

MyClass::MyClass(double value) : m_value { value }, m_foo { m_value } {
    std::cout << "MyClass::m_value = " << m_value << std::endl;
}

TEST(对象的生命周期, 初始化顺序) {
    MyClass instance { 1.2 };
}

TEST(对象的生命周期, 拷贝构造函数) {
    MyClass instance { 1.2 };
}

class EvenSequence {
public:
    EvenSequence(std::initializer_list<double> args) {
        if (args.size() % 2 != 0) {
            throw std::invalid_argument {
                "initializer_list should contain even number of elements"
            };
        }
        // m_sequence.reserve(args.size());
        // for (auto const &value : args) {
        //     m_sequence.push_back(value);
        // }
        m_sequence.assign(args);
    }

    void dump() const {
        for (auto const &value : m_sequence) {
            std::cout << value << ", ";
        }
        std::cout << std::endl;
    }

private:
    std::vector<double> m_sequence;
};

TEST(对象的生命周期, 初始化列表构造函数) {
    EvenSequence p1 { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
    p1.dump();

    try {
        EvenSequence p2 { 1.0, 2.0, 3.0 };
    } catch (std::invalid_argument const &e) {
        std::cout << e.what() << std::endl;
    }

    std::vector<std::string> myVec { "String 1", "String 2", "String 3" };
}

TEST(对象的生命周期, 转换构造函数) {
    using namespace std;
    SpreadsheetCell myCell { 4 };
    // myCell = 5;
    // myCell = "6"sv;
}

class MyClass1 {
public:
    // MyClass1(int) {}
    // MyClass1(int, int) {}
    explicit MyClass1(int) {
    }
    explicit MyClass1(int, int) {
    }
};

void process(MyClass1 const &c) {
}

TEST(对象的生命周期, 多个参数的转换构造函数) {
    // process(1);
    // process({1, 1});
    // process({1, 2});

    process(MyClass1 { 1 });
    process(MyClass1 { 1, 1 });
    process(MyClass1 { 1, 2 });
}

TEST(对象的生命周期, 销毁对象之解构子) {
    SpreadsheetCell myCell { 5 };
    if (myCell.getValue() == 5) {
        SpreadsheetCell anotherCell { 6 };
    }
    std::cout << "myCell: " << myCell.getValue() << std::endl;
}

TEST(对象的生命周期, 销毁对象之delete) {
    SpreadsheetCell *cellPtr1 { new SpreadsheetCell { 5 } };
    SpreadsheetCell *cellPtr2 { new SpreadsheetCell { 6 } };
    std::cout << "cellPtr1: " << cellPtr1->getValue() << std::endl;
    delete cellPtr1;
    cellPtr1 = nullptr;
}

TEST(对象的生命周期, 对象赋值) {
    SpreadsheetCell myCell { 5 }, anotherCell;
    anotherCell = myCell;
}

TEST(对象的生命周期, 复制和赋值) {
    SpreadsheetCell myCell { 5 };
    SpreadsheetCell anotherCell { myCell };
    SpreadsheetCell aThirdCell = myCell;
    anotherCell = myCell;

    SpreadsheetCell myCell2 { 5 };
    std::string s1;
    s1 = myCell2.getString();

    SpreadsheetCell myCell3 { 5 };
    std::string s2 = myCell3.getString();
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

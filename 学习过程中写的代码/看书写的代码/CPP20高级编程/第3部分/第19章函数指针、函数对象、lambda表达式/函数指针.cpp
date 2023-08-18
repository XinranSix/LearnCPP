#include <cstddef>
#include <format>
#include <iostream>
#include <gtest/gtest.h>
#include <span>
#include <vector>

using Matcher = bool (*)(int, int);
using MatcherHandler = void (*)(size_t, int, int);

void findMatches(std::span<const int> values1, std::span<const int> values2, Matcher matcher,
                 MatcherHandler matcherHandler) {
    if (values1.size() != values2.size()) {
        return;
    }

    for (size_t i { 0 }; i < values1.size(); ++i) {
        if (matcher(values1[i], values2[i])) {
            matcherHandler(i, values1[i], values2[i]);
        }
    }
}

bool intEqual(int item1, int item2) {
    return item1 == item2;
}

void printMatch(size_t position, int value1, int value2) {
    std::cout << std::format("Match found at position {}({}, {})", position, value1, value2)
              << std::endl;
}

bool bothOdd(int item1, int item2) {
    return item1 % 2 == 1 && item2 % 2 == 1;
}

TEST(函数指针, 函数指针的类型别名) {
    std::vector values1 { 2, 5, 6, 9, 10, 1, 1 };
    std::vector values2 { 4, 4, 2, 9, 0, 3, 1 };

    std::cout << "Calling findMatches() using intEqual():" << std::endl;
    findMatches(values1, values2, &intEqual, &printMatch);

    std::cout << "Calling findMatches() using bothOdd():" << std::endl;
    findMatches(values1, values2, &bothOdd, &printMatch);
}

/* -------------------------------------------------------------------------- */

const int DefaultStartingSalary { 30'000 };
const int DefaultRaiseAndDemeritAmount { 1'000 };

class Employee {
public:
    Employee(std::string const &firstName, std::string const &lastName);

    void promote(int raiseAmount = DefaultRaiseAndDemeritAmount); // 升职
    void demote(int demerit = DefaultRaiseAndDemeritAmount);      // 降职
    void hire();                                                  // 雇佣
    void fire();                                                  // 炒鱿鱼
    void display() const;                                         // 显示

    // 各种 setter 和 getter
    void setFirstName(std::string const &firstName);
    std::string const &getFirstName() const;

    void setLastName(std::string const &lastName);
    std::string const &getLastName() const;

    void setEmployeeNumber(int employeeNumber);
    int getEmployeeNumber() const;

    void setSalary(int newSalary);
    int getSalary() const;

    bool isHired() const;

private:
    std::string m_firstName;
    std::string m_lastName;
    int m_employeeNumber { -1 };
    int m_salary { DefaultStartingSalary };
    bool m_hired { false };
};

Employee::Employee(std::string const &firstName, std::string const &lastName)
    : m_firstName { firstName }, m_lastName { lastName } {}

void Employee::promote(int raiseAmount) {
    setSalary(getSalary() + raiseAmount);
}

void Employee::demote(int demerit) {
    setSalary(getSalary() - demerit);
}

void Employee::hire() {
    m_hired = true;
}

void Employee::fire() {
    m_hired = false;
}

void Employee::display() const {
    using namespace std;
    cout << format("Employee: {}, {}", getLastName(), getFirstName()) << endl;
    cout << "------------------------------" << endl;
    cout << (isHired() ? "Current Employee" : "Former Employee") << endl;
    cout << format("Employee Number: {}", getEmployeeNumber()) << endl;
    cout << format("Salary: ${}", getSalary()) << endl;
    cout << endl;
}

void Employee::setFirstName(std::string const &firstName) {
    m_firstName = firstName;
}

std::string const &Employee::getFirstName() const {
    return m_firstName;
}

void Employee::setLastName(std::string const &lastName) {
    m_lastName = lastName;
}

std::string const &Employee::getLastName() const {
    return m_lastName;
}

void Employee::setEmployeeNumber(int employeeNumber) {
    m_employeeNumber = employeeNumber;
}

int Employee::getEmployeeNumber() const {
    return m_employeeNumber;
}

void Employee::setSalary(int newSalary) {
    m_salary = newSalary;
}

int Employee::getSalary() const {
    return m_salary;
}

bool Employee::isHired() const {
    return m_hired;
}

TEST(函数指针, 指向方法和数据成员的指针) {
    int (Employee::*methodPtr)() const { &Employee::getSalary };
    Employee employee { "John", "Doe" };
    std::cout << (employee.*methodPtr)() << std::endl;

    Employee *employee1 { new Employee { "John", "Doe" } };
    std::cout << (employee1->*methodPtr)() << std::endl;

    using PtrToGet = int (Employee::*)() const;
    PtrToGet methodPtr1 { &Employee::getSalary };
    Employee employee2 { "John", "Doe" };
    std::cout << (employee2.*methodPtr1)() << std::endl;

    auto methodPtr2 { &Employee::getSalary };
    Employee employee3 { "John", "Doe" };
    std::cout << (employee3.*methodPtr2)() << std::endl;
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

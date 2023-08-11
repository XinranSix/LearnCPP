#include <algorithm>
#include <format>
#include <iostream>
#include <memory>

class Person {

public:
    Person() {
        std::cout << "默认构造函数" << std::endl;
    }
    Person(std::string firstName, std::string lastName)
        : m_firstName { std::move(firstName) },
          m_lastName { std::move(lastName) } {
        std::cout << "普通构造函数" << std::endl;
    }

    Person(Person const &person)
        : m_firstName { person.m_firstName }, m_lastName { person.m_lastName } {
        std::cout << "拷贝构造函数" << std::endl;
    }

    Person(Person &&person) noexcept
        : m_firstName { std::move(person.m_firstName) },
          m_lastName { std::move(person.m_lastName) } {
        std::cout << "移动构造函数" << std::endl;
        // swap(person);
    }

    ~Person() {
    }

public:
    Person &operator=(Person const &person) {
        std::cout << "拷贝赋值运算符" << std::endl;
        Person temp { person };
        swap(temp);
        return *this;
    }

    Person &operator=(Person &&person) noexcept {
        std::cout << "移动赋值运算符" << std::endl;
        swap(person);
        return *this;
    }

public:
    std::string const &getFirstName() const {
        return m_firstName;
    }
    void setFirstName(std::string const &firstName) {
        m_firstName = firstName;
    }

    std::string const &getLastName() const {
        return m_lastName;
    }
    void setLastName(std::string const &lastName) {
        m_lastName = lastName;
    }

private:
    void swap(Person &person) {
        std::swap(m_firstName, person.m_firstName);
        std::swap(m_lastName, person.m_lastName);
    }

private:
    std::string m_firstName;
    std::string m_lastName;
};

int main(int argc, char *argv[]) {

    Person person1 {};
    Person person2 { "HYT", "YJ" };
    Person person3 = person2;
    person1 = person3;
    person1 = { "HYT", "YJ" };
    Person person4 { std::move(person1) };

    return 0;
}

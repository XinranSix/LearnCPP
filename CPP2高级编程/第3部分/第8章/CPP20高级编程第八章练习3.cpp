#include <format>
#include <iostream>
#include <memory>

class Person {

public:
    Person() = default;
    Person(std::string const &firstName, std::string const &lastName)
        : m_firstName(firstName), m_lastName(lastName) {
        std::cout << "构造子" << std::endl;
    }

    Person(Person const &person)
        : m_firstName(person.m_firstName), m_lastName(person.m_lastName) {
        std::cout << "拷贝构造子" << std::endl;
    }

    ~Person() { std::cout << "解构子" << std::endl; }

public:
    Person &operator=(Person const &person) {
        std::cout << "拷贝赋值运算子 " << std::endl;
        if (this == &person) {
            return *this;
        }
        m_firstName = person.m_firstName;
        m_lastName = person.m_lastName;
        return *this;
    }

public:
    std::string const &getFirstName() const { return m_firstName; }
    void setFirstName(std::string const &firstName) { m_firstName = firstName; }

    std::string const &getLastName() const { return m_lastName; }
    void setLastName(std::string const &lastName) { m_lastName = lastName; }

private:
    std::string m_firstName;
    std::string m_lastName;
};

int main(int argc, char *argv[]) {

    Person person1;
    Person person2 = person1;
    Person person3;
    person3 = person2;

    return 0;
}

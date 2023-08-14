#include <format>
#include <iostream>
#include <memory>

class Person {

public:
    Person(std::string const &firstName, std::string const &lastName)
        : m_firstName(firstName), m_lastName(lastName) {
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
    std::string m_firstName;
    std::string m_lastName;
};

int main(int argc, char *argv[]) {

    Person person { "H", "YT" };
    std::unique_ptr<Person> personPtr { std::make_unique<Person>("Y", "J") };

    std::cout << std::format("{}{}", person.getFirstName(),
                             person.getLastName())
              << std::endl;
    std::cout << std::format("{}{}", personPtr->getFirstName(),
                             personPtr->getLastName())
              << std::endl;

    return 0;
}

#include <format>
#include <iostream>
#include <memory>

class Person {

public:
    Person() = default;
    Person(std::string const &firstName, std::string const &lastName)
        : Person { firstName, lastName,
                   std::format("{}{}", firstName[0], lastName[0]) } {
    }

    Person(std::string const &firstName, std::string const &lastName,
           std::string const &initials)
        : m_firstName { firstName }, m_lastName { lastName },
          m_initials { initials } {
    }

    // Person(Person const &person) = delete;

    // ~Person() = delete;
    ~Person() {
        std::cout << "解构子" << std::endl;
    }

public:
    // Person &operator=(Person const &person) = delete;

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

    std::string const &getFirstLatter() const {
        return m_initials;
    }
    void setFirstLatter(std::string const &initials) {
        m_initials = initials;
    }

private:
    std::string m_firstName;
    std::string m_lastName;
    std::string m_initials;
};

int main(int argc, char *argv[]) {

    Person person { "HYT", "YJ" };

    return 0;
}

#include <iostream>
#include <filesystem>
#include <format>
#include <string>
#include <ostream>
#include <sstream>
#include <fstream>

class Person {
public:
    Person() {}

    Person(std::string const &firstName, std::string const &lastName)
        : Person { firstName, lastName,
                   std::format("{}{}", firstName[0], lastName[0]) } {}

    Person(std::string const &firstName, std::string const &lastName,
           std::string const &initials)
        : m_firstName { firstName }, m_lastName { lastName },
          m_initials { initials } {}

    ~Person() {}

public:
    [[nodiscard]] auto operator<=>(Person const &) const = default;
    // [[nodiscard]] bool operator==(Person const &) const = default;

public:
    friend std::ostream &operator<<(std::ostream &os, Person const &person);
    friend std::istream &operator>>(std::istream &os, Person &person);

public:
    void output(std::ostream &os) {

        os << std::format("{}{} {}", m_firstName, m_lastName, m_initials)
           << std::endl;
    }

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

    std::string const &getInitials() const {
        return m_initials;
    }
    void setInitials(std::string const &initials) {
        m_initials = initials;
    }

private:
    std::string m_firstName;
    std::string m_lastName;
    std::string m_initials;
};

std::ostream &operator<<(std::ostream &os, Person const &person) {
    return os << person.m_firstName << ' ' << person.m_lastName << ' '
              << person.m_initials;
}

std::istream &operator>>(std::istream &is, Person &person) {
    return is >> person.m_firstName >> person.m_lastName >> person.m_initials;
}

int main(int argc, char *argv[]) {

    return 0;
}

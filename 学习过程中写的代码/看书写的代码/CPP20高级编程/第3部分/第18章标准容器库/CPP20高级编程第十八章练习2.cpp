#include <utility>
#include <vector>
#include <iostream>
#include <filesystem>
#include <format>
#include <map>
#include <string>
#include <ostream>
#include <sstream>
#include <fstream>

class Person {
public:
    Person() {}

    Person(std::string const &firstName, std::string const &lastName)
        : Person { firstName, lastName, std::format("{}{}", firstName[0], lastName[0]) } {}

    Person(std::string const &firstName, std::string const &lastName, std::string const &initials)
        : m_firstName { firstName }, m_lastName { lastName }, m_initials { initials } {}

    ~Person() {}

public:
    [[nodiscard]] auto operator<=>(Person const &) const = default;
    [[nodiscard]] bool operator==(Person const &) const = default;

public:
    operator std::string() {
        return m_firstName + m_lastName;
    }

public:
    friend std::ostream &operator<<(std::ostream &os, Person const &person);
    friend std::istream &operator>>(std::istream &os, Person &person);

public:
    void output(std::ostream &os) {

        os << std::format("{}{} {}", m_firstName, m_lastName, m_initials) << std::endl;
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
    return os << person.m_firstName << ' ' << person.m_lastName << ' ' << person.m_initials;
}

std::istream &operator>>(std::istream &is, Person &person) {
    return is >> person.m_firstName >> person.m_lastName >> person.m_initials;
}

Person operator""_p(const char *s, size_t) {
    std::istringstream input { s };

    std::string firstName, lastName;

    input >> firstName;

    input >> std::ws;

    getline(input, lastName);

    return Person { std::move(firstName), std::move(lastName) };
}

/* -------------------------------------------------------------------------- */

class PhoneBook {
public:
    void addPhoneNumber(const Person &person, std::string_view phoneNumber);
    void removePhoneNumber(const Person &person, std::string_view phoneNumber);
    std::vector<std::string> getPhoneNumbers(const Person &person) const;

private:
    std::multimap<Person, std::string> m_phoneBook;
};

void PhoneBook::addPhoneNumber(const Person &person, std::string_view phoneNumber) {
    m_phoneBook.insert(std::pair { person, phoneNumber });
}

void PhoneBook::removePhoneNumber(const Person &person, std::string_view phoneNumber) {
    auto [begin, end] { m_phoneBook.equal_range(person) };
    for (auto it { begin }; it != end; ++it) {
        if (it->second == phoneNumber) {
            m_phoneBook.erase(it);
            return;
        }
    }
}

std::vector<std::string> PhoneBook::getPhoneNumbers(const Person &person) const {
    std::vector<std::string> res;
    auto [begin, end] { m_phoneBook.equal_range(person) };
    for (auto it { begin }; it != end; ++it) {
        res.push_back(it->second);
    }
    return res;
}

int main(int argc, char *argv[]) {

    PhoneBook phoneBook;
    phoneBook.addPhoneNumber("John Doe"_p, "123-456-789");
    phoneBook.addPhoneNumber("Jane Doe"_p, "789-456-123");
    phoneBook.addPhoneNumber("John Doe"_p, "999-456-789");
    phoneBook.addPhoneNumber("Marc Gregoire"_p, "258-369-147");
    phoneBook.removePhoneNumber("Marc Gregoire"_p, "258-369-147");
    phoneBook.removePhoneNumber("Marc G"_p, "258-369-147");

    std::cout << "John Doe's phone numbers:" << std::endl;
    for (const auto &number : phoneBook.getPhoneNumbers("John Doe"_p)) {
        std::cout << "\t" << number << std::endl;
    }

    return 0;
}

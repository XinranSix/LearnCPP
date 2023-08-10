#include <format>
#include <iostream>
#include <memory>

class Person {
public:
    Person();
    Person(std::string firstName, std::string lastName);
    Person(std::string firstName, std::string lastName, std::string initials);
    ~Person();
    Person(Person const &person);
    Person(Person &&person) noexcept;
    Person &operator=(Person const &perons);
    Person &operator=(Person &&person) noexcept;

    const std::string &getFirstName() const;
    void setFirstName(std::string firstName);

    const std::string &getLastName() const;
    void setLastName(std::string lastName);

    const std::string &getInitials() const;
    void setInitials(std::string initials);

private:
    class Impl;
    std::unique_ptr<Impl> m_impl;
};

class Person::Impl {
public:
    Impl() = default;
    Impl(std::string firstName, std::string lastName);
    Impl(std::string firstName, std::string lastName, std::string initials);

    const std::string &getFirstName() const;
    void setFirstName(std::string firstName);

    const std::string &getLastName() const;
    void setLastName(std::string lastName);

    const std::string &getInitials() const;
    void setInitials(std::string initlials);

private:
    std::string m_firstName;
    std::string m_lastName;
    std::string m_initials;
};

Person::Impl::Impl(std::string firstName, std::string lastName)
    : Impl { std::move(firstName), std::move(lastName),
             std::format("{}{}", firstName[0], lastName[0]) } {
}

Person::Impl::Impl(std::string firstName, std::string lastName,
                   std::string initials)
    : m_firstName { std::move(firstName) }, m_lastName { std::move(lastName) },
      m_initials { std::move(initials) } {
}

const std::string &Person::Impl::getFirstName() const {
    return m_firstName;
}

void Person::Impl::setFirstName(std::string firstName) {
    m_firstName = std::move(firstName);
}

const std::string &Person::Impl::getLastName() const {
    return m_lastName;
}

void Person::Impl::setLastName(std::string lastName) {
    m_lastName = std::move(lastName);
}

const std::string &Person::Impl::getInitials() const {
    return m_initials;
}

void Person::Impl::setInitials(std::string initials) {
    m_initials = std::move(initials);
}

/* -------------------------------------------------------------------------- */

Person::Person(std::string firstName, std::string lastName)
    : m_impl { std::make_unique<Impl>(std::move(firstName),
                                      std::move(lastName)) } {
}

Person::Person(std::string firstName, std::string lastName,
               std::string initials)
    : m_impl { std::make_unique<Impl>(std::move(firstName),
                                      std::move(lastName)) } {
}

Person::Person() : m_impl { std::make_unique<Impl>() } {
}

Person::~Person() = default;
Person::Person(Person &&) noexcept = default;
Person &Person::operator=(Person &&) noexcept = default;

Person::Person(Person const &person)
    : m_impl { std::make_unique<Impl>(*person.m_impl) } {
}

Person &Person::operator=(Person const &person) {
    *m_impl = *person.m_impl;
    return *this;
}

const std::string &Person::getFirstName() const {
    return m_impl->getFirstName();
}

void Person::setFirstName(std::string firstName) {
    m_impl->setFirstName(std::move(firstName));
}

const std::string &Person::getLastName() const {
    return m_impl->getLastName();
}

void Person::setLastName(std::string lastName) {
    m_impl->setLastName(std::move(lastName));
};

const std::string &Person::getInitials() const {
    return m_impl->getInitials();
}

void Person::setInitials(std::string initials) {
    m_impl->setInitials(std::move(initials));
}

int main(int argc, char *argv[]) {

    Person person { "John", "Doe" };
    std::cout << format("The initials of {} {} are {}.", person.getFirstName(),
                        person.getLastName(), person.getInitials())
              << std::endl;

    Person person2 { "Marc", "Gregoire", "Mg" };
    std::cout << format("The initials of {} {} are {}.", person2.getFirstName(),
                        person2.getLastName(), person2.getInitials())
              << std::endl;

    Person persons[3];

    // Test copy constructor.
    Person copy { person };

    // Test assignment operator.
    Person otherPerson { "Jane", "Doe" };
    copy = otherPerson;

    // Test move construction.
    Person moved { std::move(copy) };

    // Test move assignment operator.
    Person moved2;
    moved2 = std::move(otherPerson);

    return 0;
}

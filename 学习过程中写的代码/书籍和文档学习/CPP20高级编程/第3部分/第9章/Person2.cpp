#include <iostream>
#include <memory>
#include <string>
#include <stddef.h>
#include <utility>

class Person {
public:
    Person();
    Person(std::string name, size_t age, size_t height);
    ~Person();
    Person(Person const &person);
    Person(Person &&person) noexcept;

    Person &operator=(Person const &person);
    Person &operator=(Person &&person) noexcept;

public:
    std::string const &getName() const;
    void setName(std::string firstName);

    size_t getAge() const;
    void setAge(size_t age);

    size_t getHeight() const;
    void setHeight(size_t height);

private:
    class Impl;
    std::unique_ptr<Impl> m_impl;
};

class Person::Impl {
public:
    Impl() = default;
    Impl(std::string name, size_t age, size_t height);

    std::string const &getName() const;
    void setName(std::string name);

    size_t getAge() const;
    void setAge(size_t age);

    size_t getHeight() const;
    void setHeight(size_t height);

private:
    std::string m_name;
    size_t m_age;
    size_t m_height;
};

Person::Impl::Impl(std::string name, size_t age, size_t height)
    : m_name { std::move(name) }, m_age { std::exchange(age, 0) },
      m_height { std::exchange(height, 0) } {
}

std::string const &Person::Impl::getName() const {
    return m_name;
}

void Person::Impl::setName(std::string name) {
    m_name = std::move(name);
}

size_t Person::Impl::getAge() const {
    return m_age;
}

void Person::Impl::setAge(size_t age) {
    m_age = std::exchange(age, 0);
}

size_t Person::Impl::getHeight() const {
    return m_age;
}

void Person::Impl::setHeight(size_t height) {
    m_height = std::exchange(height, 0);
}
/* -------------------------------------------------------------------------- */

Person::Person() : m_impl { std::make_unique<Impl>() } {
}

Person::Person(std::string name, size_t age, size_t height) {
}

Person::~Person() = default;

Person::Person(Person const &person)
    : m_impl { std::make_unique<Impl>(*person.m_impl) } {
}

Person::Person(Person &&person) noexcept = default;

Person &Person::operator=(Person const &person) {
    *m_impl = *person.m_impl;
    return *this;
}

Person &Person::operator=(Person &&person) noexcept = default;
std::string const &Person::getName() const {
    return m_impl->getName();
}

void Person::setName(std::string firstName) {
    m_impl->setName(std::move(firstName));
}

size_t Person::getAge() const {
    return m_impl->getAge();
}

void Person::setAge(size_t age) {
    m_impl->setAge(std::exchange(age, 0));
}

size_t Person::getHeight() const {
    return m_impl->getHeight();
}

void Person::setHeight(size_t height) {
    m_impl->setHeight(std::exchange(height, 0));
}

int main(int argc, char *argv[]) {
    return 0;
}

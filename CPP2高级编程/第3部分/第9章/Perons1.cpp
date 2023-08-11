#include <iostream>
#include <string>
#include <utility>

class Person {
public:
    Person();
    Person(std::string name, size_t age, size_t height);
    ~Person();
    Person(Person const &person);
    Person(Person &&person) noexcept;

public:
    Person &operator=(Person const &person);
    Person &operator=(Person &&person) noexcept;

    [[nodiscard]] bool operator==(Person const &person);
    [[nodiscard]] auto operator<=>(Person const &person);

public:
    std::string const &getName() const {
        return m_name;
    }
    void setName(std::string name) {
        m_name = std::move(name);
    }

    size_t getAge() const {
        return m_age;
    }
    void setAge(size_t age) {
        m_age = age;
    }

    size_t getHeight() const {
        return m_height;
    }
    void setHeight(size_t height) {
        m_height = height;
    }

private:
    void swap(Person &person);

private:
    std::string m_name;
    size_t m_age;
    size_t m_height;
};

Person::Person() {
}

Person::Person(std::string name, size_t age, size_t height)
    : m_name { std::move(name) }, m_age { age }, m_height { height } {
}

Person::~Person() {
}

Person::Person(Person const &person)
    : m_name { person.m_name }, m_age { person.m_age },
      m_height { person.m_height } {
}

Person::Person(Person &&person) noexcept
    : m_name { std::move(person.m_name) },
      m_age { std::exchange(person.m_age, 0) },
      m_height { std::exchange(person.m_height, 0) } {
    // swap(person);
}

Person &Person::operator=(Person const &person) {
    Person temp { person };
    swap(temp);
    return *this;
}

Person &Person::operator=(Person &&person) noexcept {
    swap(person);
    return *this;
}

bool Person::operator==(Person const &person) {
    return m_age == person.m_age;
}

auto Person::operator<=>(Person const &person) {
    return m_age <=> person.m_height;
}

void Person::swap(Person &person) {
    std::swap(m_name, person.m_name);
    m_age = std::exchange(person.m_age, 0);
    m_height = std::exchange(person.m_height, 0);
}

int main(int argc, char *argv[]) {
    return 0;
}

#include <format>
#include <iostream>
#include <ostream>
#include <string>

class Person {
public:
    std::string name;
    std::string position;
    std::string date_of_birth;

    friend std::ostream &operator<<(std::ostream &os, Person const &obj) {
        return os << std::format("name: {} position: {} date_of_birth: {}",
                                 obj.name, obj.position, obj.date_of_birth);
    }
};

class PersonBuilder {
protected:
    Person person;

public:
    [[nodiscard]] Person build() const { return person; }
};

template <typename TSelf>
class PersonInfoBuilder : public PersonBuilder {
public:
    TSelf &called(std::string const &name) {
        person.name = name;
        return static_cast<TSelf &>(*this);
    }
};

template <typename TSelf>
class PersonJobBuilder : public PersonInfoBuilder<PersonJobBuilder<TSelf>> {
public:
    TSelf &works_as(std::string const &position) {
        this->person.position = position;
        return static_cast<TSelf &>(*this);
    }
};

template <typename TSelf>
class PersonBirthDateBuilder
    : public PersonJobBuilder<PersonBirthDateBuilder<TSelf>> {
public:
    TSelf &born_on(std::string const &data_of_birth) {
        this->person.date_of_birth = data_of_birth;
        return static_cast<TSelf &>(*this);
    }
};

class MyBuilder : public PersonBirthDateBuilder<MyBuilder> {};

int main(int argc, char *argv[]) {

    MyBuilder mb;

    auto me { mb.called("HYT").works_as("WIT").born_on("2003/3/12").build() };

    std::cout << me << std::endl;

    return 0;
}

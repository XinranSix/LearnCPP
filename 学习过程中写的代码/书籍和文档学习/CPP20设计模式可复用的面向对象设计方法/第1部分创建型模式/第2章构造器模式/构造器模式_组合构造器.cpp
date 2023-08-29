#include <iostream>
#include <string>

class PersonBuilderBase;
class PersonBuilder;
class PersonAddressBuilder;
class PersonJobBuilder;

struct Person {

    // friend class PersonBuilderBase;
    // friend class PersonAddressBuilder;

    std::string street_address;
    std::string post_code;
    std::string city;

    std::string company_name;
    std::string position;
    int annual_income = 0;

    Person() {}

    // static PersonBuilder create() { return PersonBuilder {}; }
};

class PersonBuilderBase {
protected:
    Person &person;

    explicit PersonBuilderBase(Person &person) : person { person } {}

public:
    operator Person() { return std::move(person); }

    PersonAddressBuilder lives() const;
    PersonJobBuilder works() const;
};

class PersonBuilder : public PersonBuilderBase {
    Person p;

public:
    PersonBuilder() : PersonBuilderBase { p } {}
};

class PersonAddressBuilder : public PersonBuilderBase {
    using self = PersonAddressBuilder;

public:
    explicit PersonAddressBuilder(Person &person)
        : PersonBuilderBase { person } {}

    self &at(std::string street_address) {
        person.street_address = street_address;
        return *this;
    }

    self &with_postcode(std::string post_code) {
        person.post_code = post_code;
        return *this;
    }

    self &in(std::string city) {
        person.city = city;
        return *this;
    }
};

class PersonJobBuilder : public PersonBuilderBase {
    using self = PersonJobBuilder;

public:
    explicit PersonJobBuilder(Person &person) : PersonBuilderBase { person } {}

    self &at(std::string company_name) {
        person.company_name = company_name;
        return *this;
    }

    self &as_a(std::string position) {
        person.position = position;
        return *this;
    }

    self &in(int annual_income) {
        person.annual_income = annual_income;
        return *this;
    }
};

int main(int argc, char *argv[]) {

    // Person p = Person::create().

    return 0;
}

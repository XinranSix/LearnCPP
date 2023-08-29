#include <iostream>
#include <memory>
#include <string>
#include <utility>

class Address {
public:
    std::string street;
    std::string city;
    int suite;

    Address() = default;
    Address(std::string street, std::string city, int suite)
        : street { std::move(street) }, city { std::move(city) }, suite(suite) {
    }

    virtual Address *clone() { return new Address { street, city, suite }; }
};

class Contact {
public:
    std::string name;
    Address *address;

    Contact(std::string name, Address *address)
        : name { name }, address { address } {}

    Contact(Contact const &other)
        : name { other.name }, address { new Address { *other.address } } {}

    Contact &operator=(Contact const &other) {
        if (this == &other) {
            return *this;
        }
        name = other.name;
        address = other.address;
        return *this;
    }

    ~Contact() { delete address; }
};

class EmployeeFactory {
    static Contact main;
    static Contact aux;

    static std::unique_ptr<Contact> NewEmployee(std::string name, int suite,
                                                Contact &proto) {
        auto result { std::make_unique<Contact>(proto) };
        result->name = std::move(name);
        result->address->suite = suite;
        return result;
    }

public:
    static std::unique_ptr<Contact> NewMainOfficeEmployee(std::string name,
                                                          int suite) {
        return NewEmployee(std::move(name), suite, main);
    }

    static std::unique_ptr<Contact> NewAuxOfficeEmployee(std::string name,
                                                         int suite) {
        return NewEmployee(std::move(name), suite, aux);
    }
};

Contact EmployeeFactory::main { "",
                                new Address { "123 East Dr", "London", 0 } };

Contact EmployeeFactory::aux { "",
                               new Address { "123B East Dr", "London", 0 } };

int main(int argc, char *argv[]) {

    auto john { EmployeeFactory::NewAuxOfficeEmployee("John Doe", 123) };
    auto jane { EmployeeFactory::NewAuxOfficeEmployee("Jane Doe", 125) };

    return 0;
}

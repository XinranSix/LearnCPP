#include <iostream>
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

class ExtendedAddress : public Address {
public:
    std::string country;
    std::string postcode;

    ExtendedAddress(std::string street, std::string city, int suite,
                    std::string country, std::string postcode)
        : Address { std::move(street), std::move(city), suite },
          country { std::move(country) }, postcode { std::move(postcode) } {}

    virtual ExtendedAddress *clone() override {
        return new ExtendedAddress { street, city, suite, country, postcode };
    }
};

int main(int argc, char *argv[]) {

    ExtendedAddress ea { "123 West Dr", "London", 123, "UK", "SW101EG" };
    Address &a = ea;
    auto cloned { a.clone() };

    return 0;
}

#include <iostream>
#include <string>

class Address {
public:
    std::string street;
    std::string city;
    int suite;

    // Address() {}
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

int main(int argc, char *argv[]) {

    Contact worker { "", new Address { "123", "London", 0 } };
    Contact john { worker };
    john.name = "John";
    john.address->suite = 10;

    return 0;
}

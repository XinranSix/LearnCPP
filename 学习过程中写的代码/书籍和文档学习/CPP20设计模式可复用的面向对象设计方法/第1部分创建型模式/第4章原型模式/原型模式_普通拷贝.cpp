#include <iostream>
#include <string>

class Address {
public:
    std::string street;
    std::string city;
    int suite;
};

class Contact {
public:
    std::string name;
    Address address;
};

int main(int argc, char *argv[]) {

    Contact worker { "", Address { "123 East Dr", "London", 0 } };
    Contact john = worker;
    john.name = "John Doe";
    john.address.suite = 10;

    return 0;
}

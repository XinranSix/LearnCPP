#include "boost/serialization/access.hpp"
#include "fmt/core.h"
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <iostream>
#include <sstream>
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

private:
    friend class boost::serialization::access;

    template <typename Ar>
    void serialize(Ar &ar, unsigned int const version) {
        ar &street;
        ar &city;
        ar &suite;
    }
};

class Contact {
public:
    std::string name;
    Address *address {};

    Contact() = default;

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

private:
    friend class boost::serialization::access;

    template <typename Ar>
    void serialize(Ar &ar, unsigned int const version) {
        ar &name;
        ar &address;
    }
};

template <typename T>
T clone(T obj) {
    // 序列化
    std::ostringstream oss;
    boost::archive::text_oarchive oa { oss };
    oa << obj;
    std::string s = oss.str();

    fmt::print("{}\n", s);

    // 反序列化
    std::istringstream iss { oss.str() };
    boost::archive::text_iarchive ia { iss };
    T result;
    ia >> result;

    return result;
}

int main(int argc, char *argv[]) {

    Contact john { "John", new Address { "123", "London", 10 } };
    Contact jane = clone(john);
    jane.name = "Jane";

    return 0;
}

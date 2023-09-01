#include <cstdint>
#include <iostream>
#include <map>
#include <ostream>
#include <string>
#include <type_traits>
#include <utility>
#include "boost/bimap.hpp"
#include "boost/flyweight.hpp"
#include "boost/flyweight/flyweight_fwd.hpp"
#include "fmt/core.h"

using key = uint16_t;

struct User {
    boost::flyweight<std::string> first_name, last_name;

    User(std::string const &first_name, std::string const &last_name)
        : first_name { first_name }, last_name { last_name } {}
};

int main(int argc, char *argv[]) {

    User john_doe { "John", "Doe" };
    User jane_doe { "Jane", "Doe" };

    fmt::print("{}\n", &jane_doe.last_name.get() == &john_doe.last_name.get());

    return 0;
}

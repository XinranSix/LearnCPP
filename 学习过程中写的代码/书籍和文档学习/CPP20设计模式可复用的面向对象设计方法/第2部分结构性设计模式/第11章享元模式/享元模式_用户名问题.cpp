#include <cstdint>
#include <iostream>
#include <map>
#include <ostream>
#include <string>
#include <utility>
#include "boost/bimap.hpp"

using key = uint16_t;

struct User {
    User(std::string first_name, std::string last_name)
        : first_name { add(std::move(first_name)) },
          last_name { add(std::move(last_name)) } {}

    std::string const &get_first_name() const {
        return names.left.find(first_name)->second;
    }

    std::string const &get_last_name() const {
        return names.left.find(last_name)->second;
    }

    friend std::ostream &operator<<(std::ostream &os, User const &obj) {
        return os << "first_name: " << obj.get_first_name()
                  << " last_name: " << obj.get_last_name();
    }

protected:
    key first_name, last_name;
    static boost::bimap<key, std::string> names;
    static key seed;
    static key add(std::string s) {

        auto it { names.right.find(s) };
        if (it == names.right.end()) {
            names.insert({ ++seed, s });
        }
        return it->second;
    }
};

int main(int argc, char *argv[]) { return 0; }

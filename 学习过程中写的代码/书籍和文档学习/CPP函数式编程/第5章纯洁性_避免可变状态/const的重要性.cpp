#include "fmt/core.h"
#include <iostream>
#include <string>
#include <type_traits>

int main(int argc, char *argv[]) {

    std::string const name { "HYT" };

    std::string name_cpoy = name;
    // std::string &name_ref = name;// Error
    std::string const name_constref = name;
    // std::string *name_ptr = &name; // Error
    std::string const *name_constptr = &name;

    return 0;
}

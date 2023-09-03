#include <iostream>
#include "boost/version.hpp"
#include "boost/config.hpp"
#include "fmt/core.h"

int main(int argc, char *argv[]) {

    fmt::print("{}\n", BOOST_VERSION);
    fmt::print("{}\n", BOOST_LIB_VERSION);
    fmt::print("{}\n", BOOST_PLATFORM);
    fmt::print("{}\n", BOOST_COMPILER);
    fmt::print("{}\n", BOOST_STDLIB);

    return 0;
}

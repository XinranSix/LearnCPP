#include <boost/core/noncopyable.hpp>
#include <iostream>
#include "boost/noncopyable.hpp"

class do_not_copy : boost::noncopyable {};

int main(int argc, char *argv[]) {

    do_not_copy d1;
    // do_not_copy d2 { d1 };
    do_not_copy d3;
    // d3 = d1;

    return 0;
}

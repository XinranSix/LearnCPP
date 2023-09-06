#include <iostream>
#include "boost/core/lightweight_test.hpp"
#include "boost/core/lightweight_test_trait.hpp"
#include <type_traits>

int main(int argc, char *argv[]) {

    BOOST_TEST_TRAIT_TRUE((std::is_integral<int>));
    BOOST_TEST_TRAIT_FALSE((std::is_function<int>));

    return boost::report_errors();
}

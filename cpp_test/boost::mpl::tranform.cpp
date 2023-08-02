#include <iostream>
#include <boost/static_assert.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/int.hpp>

namespace mpl = boost::mpl;

int main(int arvc, char *argv[]) {

    BOOST_STATIC_ASSERT(
        (mpl::plus<mpl::int_<2>, mpl::int_<3>>::type::value == 5));

    return 0;
}

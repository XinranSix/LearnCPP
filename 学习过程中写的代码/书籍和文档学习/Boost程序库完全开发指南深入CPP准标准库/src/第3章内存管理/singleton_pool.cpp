#include <iostream>
#include "boost/pool/singleton_pool.hpp"

struct pool_tag {};

using spl = boost::singleton_pool<pool_tag, sizeof(int)>;

int main(int argc, char *argv[]) {

    int *p { (int *)spl::malloc() };
    assert(spl::is_from(p));
    spl::release_memory();

    return 0;
}

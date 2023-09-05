#include <iostream>
#include "boost/pool/pool.hpp"

int main(int argc, char *argv[]) {

    boost::pool<> p1 { sizeof(int) };

    int *p = static_cast<int *>(p1.malloc());
    assert(p1.is_from(p));

    p1.free(p);
    for (int i { 0 }; i < 100; ++i) {
        p1.ordered_malloc(10);
    }

    return 0;
}

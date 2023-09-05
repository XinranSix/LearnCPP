#include <iostream>
#include <boost/core/ignore_unused.hpp>

int func(int x, int y) {
    int i {};
    boost::ignore_unused(x, i);

    return y;
}

void fun2() {
    using result_type = int;
    boost::ignore_unused<result_type>();
}

int main(int argc, char *argv[]) { return 0; }

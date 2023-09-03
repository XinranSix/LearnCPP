#include <iostream>
#include <boost/core/ignore_unused.hpp>

int main(int argc, char *argv[]) {
    std::cout << "Hello World" << std::endl;

    int a { 133 };
    int b { 123 };
    int c { 123 };
    
    boost::ignore_unused(b);

    return 0;
}

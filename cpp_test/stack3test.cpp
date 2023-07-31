#include <exception>
#include <iostream>
#include <deque>
#include <cstdlib>
#include "basics/stack3.hpp"

int main(int arvc, char *argv[]) {

    try {
        Stack<int> intStack;
        Stack<double, std::deque<double>> dblStack;
        intStack.push(7);
        std::cout << intStack.top() << std::endl;
        intStack.pop();
        dblStack.push(42.42);
        std::cout << dblStack.top() << std::endl;
        dblStack.pop();
        dblStack.pop();
    } catch (std::exception const &ex) {
        std::cerr << "Exception: " << ex.what() << std::endl;
        return EXIT_FAILURE;
    }

    return 0;
}

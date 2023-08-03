#include <exception>
#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include "basics/stack8.hpp"

int main(int arvc, char *argv[]) {

    try {
        Stack<int> intStack;
        Stack<float> floatStack;
        intStack.push(42);
        intStack.push(7);
        floatStack.push(7.7);
        floatStack = intStack;
        std::cout << floatStack.top() << std::endl;
        floatStack.pop();
        std::cout << floatStack.top() << std::endl;
        floatStack.pop();
        std::cout << floatStack.top() << std::endl;
        floatStack.pop();

    } catch (std::exception const &ex) {
        std::cerr << "Exception: " << ex.what() << std::endl;
    }

    Stack<int, std::vector> vStack;
    vStack.push(42);
    vStack.push(7);
    std::cout << vStack.top() << std::endl;
    vStack.pop();

    return 0;
}

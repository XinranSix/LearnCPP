#include <iostream>
#include <string>
#include <cstdlib>
#include "basics/stack4.hpp"

int main(int arvc, char *argv[]) {

    try {
        Stack<int, 20> int20Stack;
        Stack<int, 40> int40Stack;
        Stack<std::string, 40> stringStack;
        int20Stack.push(7);
        std::cout << int20Stack.top() << std::endl;
        int20Stack.pop();
        stringStack.push("hello");
        std::cout << stringStack.top() << std::endl;
        stringStack.pop();
        stringStack.pop();
    } catch (std::exception const &ex) {
        std::cerr << "Exception: " << ex.what() << std::endl;
        return EXIT_FAILURE;
    }

    return 0;
}

#include <exception>
#include <iostream>
#include <string>
#include <cstdlib>
#include "basics/stack1.hpp"

using IntStack = Stack<int>;
void foo(IntStack const &s) { IntStack istack[10]; }

Stack<float *> floatPtrStack;
Stack<Stack<int>> intStackStack;

int main(int arvc, char *argv[]) {

    try {

        Stack<int> initStack;
        Stack<std::string> stringStack;

        initStack.push(7);
        std::cout << initStack.top() << std::endl;

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

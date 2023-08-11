#include <iostream>
#include <string>

void printString(std::string const &myString) {
    std::cout << myString << std::endl;
}

int main(int arvc, char *argv[]) {

    std::string someString{"Hello World"};
    printString(someString);
    printString("Hello World");

    return 0;
}

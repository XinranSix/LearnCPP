#include <exception>
#include <fstream>
#include <iostream>

void funcOne();
void funcTwo();

int main(int argc, char *argv[]) {

    try {
        funcOne();
    } catch (std::exception const &e) {
        std::cout << "Exception caught!" << std::endl;
        // return 1;
    }

    return 0;
}

void funcOne() {
    std::string str1;
    std::string *str2 { new std::string {} };
    funcTwo();
    delete str2;
}

void funcTwo() {
    std::ifstream fileStream;
    fileStream.open("filename");
    throw std::exception {};
    fileStream.close();
}

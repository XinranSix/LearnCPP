#include <exception>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>

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
    auto str2 { std::make_unique<std::string>("hello") };
    funcTwo();
}

void funcTwo() {
    std::ifstream fileStream;
    fileStream.open("filename");
    throw std::exception {};
    fileStream.close();
}

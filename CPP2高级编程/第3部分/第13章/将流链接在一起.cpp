#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char *argv[]) {

    std::ifstream inFile { "input.txt" };
    std::ofstream outFile { "output.txt" };

    inFile.tie(&outFile);

    outFile << "Hello there!";

    std::string nextToken;
    inFile >> nextToken;

    std::cout << nextToken << std::endl;

    return 0;
}

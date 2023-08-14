#include <iostream>
#include <sstream>

int main(int argc, char *argv[]) {

    std::cout
        << "Enter tokens. "
        << "Control+D (Unix) or Control+Z (Windows) followed by Enter to end."
        << std::endl;

    std::ostringstream outStream;
    while (std::cin) {
        std::string nextToken;
        std::cout << "Next token: ";
        std::cin >> nextToken;
        if (!std::cin || nextToken == "done") {
            break;
        }
        outStream << nextToken << "\t";
    }
    std::cout << "The end result is: " << outStream.str();

    return 0;
}

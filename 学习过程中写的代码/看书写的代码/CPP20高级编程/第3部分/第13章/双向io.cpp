#include <iostream>
#include <fstream>
#include <string>
#include <string_view>

bool changeNumberForID(std::string_view filename, int id,
                       std::string_view newNumber) {
    std::fstream ioData { filename.data() };
    if (!ioData) {
        std::cerr << "Error while opening file " << filename << std::endl;
        return false;
    }

    while (ioData) {
        int idRead {};
        std::string number;
        ioData >> idRead;
        if (!ioData) {
            break;
        }
        if (idRead == id) {
            ioData.seekp(ioData.tellg());
            ioData << " " << newNumber;
            break;
        }
        ioData >> number;
    }
    return true;
}

int main(int argc, char *argv[]) {
    changeNumberForID("input.txt", 124, "408-555-2134");
    // 408-555-0394
    return 0;
}

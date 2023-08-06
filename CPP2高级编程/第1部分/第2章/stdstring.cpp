#include <compare>
#include <iostream>
#include <string>

int main(int arvc, char *argv[]) {

    std::string a{"12"};
    std::string b{"34"};
    std::string c = a + b;
    std::cout << c << std::endl;

    // a += b;
    std::cout << a << std::endl;

    auto result{a.compare(b)};

    if (result < 0) {
        std::cout << "less" << std::endl;
    }
    if (result > 0) {
        std::cout << "greater" << std::endl;
    }
    if (result == 0) {
        std::cout << "equal" << std::endl;
    }

    auto result1{a <=> b};
    if (std::is_lt(result1)) {
        std::cout << "less" << std::endl;
    }
    if (std::is_gt(result1)) {
        std::cout << "greater" << std::endl;
    }
    if (std::is_eq(result1)) {
        std::cout << "equal" << std::endl;
    }

    std::string myString{"hello"};
    myString += ", there";
    std::string myOtherString{myString};
    if (myString == myOtherString) {
        myOtherString[0] = 'H';
    }
    std::cout << myString << std::endl;
    std::cout << myOtherString << std::endl;

    return 0;
}

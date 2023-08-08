#include <iostream>
#include <string>
#include <format>

int main(int argc, char *argv[]) {

    std::string s1;
    getline(std::cin, s1);
    std::string s2;
    getline(std::cin, s2);

    if (std::is_lt(s1 <=> s2)) {
        std::cout << s1 << std::endl << s2 << std::endl;
    } else {
        std::cout << s2 << std::endl << s1 << std::endl;
    }

    return 0;
}

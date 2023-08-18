#include <any>
#include <iostream>

int main(int argc, char *argv[]) {

    using namespace std;

    std::any empty;
    std::any anInt { 3 };
    std::any aString { "An std::string."s };

    std::cout << "empty.has_value = " << empty.has_value() << std::endl;
    std::cout << "anInt.has_value = " << anInt.has_value() << std::endl;

    std::cout << "anInt wrapped type = " << anInt.type().name() << std::endl;
    std::cout << "aString wrapped type = " << aString.type().name() << std::endl;

    int theInt { std::any_cast<int>(anInt) };
    std::cout << theInt << std::endl;
    try {
        int test { std::any_cast<int>(aString) };
        std::cout << test << std::endl;
    } catch (std::bad_any_cast const &ex) {
        std::cout << ex.what() << std::endl;
    }

    any something { 3 };
    something = "An std::string"s;

    return 0;
}

#include <iostream>
#include <limits>
#include <string>

template <typename TFrom, typename TTo>
class Converter {
public:
    virtual TTo Convert(TFrom const &from) = 0;
    virtual TFrom ConvertBack(TTo const &to) = 0;
};

class IntTOStringConverter : Converter<int, std::string> {
public:
    std::string Convert(const int &from) override {
        return std::to_string(from);
    }

    int ConvertBack(std::string const &to) override {
        int result {};
        try {
            result = std::stoi(to);
        } catch (...) { return std::numeric_limits<int>::min(); }
        return result;
    }
};

int main(int argc, char *argv[]) {

    IntTOStringConverter converter;
    std::cout << converter.Convert(123) << "\n";
    std::cout << converter.ConvertBack("456") << "\n";
    std::cout << converter.ConvertBack("xyz") << "\n";

    return 0;
}

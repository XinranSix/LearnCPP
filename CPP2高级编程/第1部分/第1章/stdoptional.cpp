#include <iostream>
#include <format>
#include <optional>

std::optional<int> getData(bool giveIt) {
    if (giveIt) {
        return 42;
    }
    return std::nullopt;
}

int main(int arvc, char *argv[]) {
    std::optional<int> data1{getData(true)};
    std::optional<int> data2{getData(false)};

    std::cout << "data1.has_value = " << data1.has_value() << std::endl;
    if (data2) {
        std::cout << "data2 has a value." << std::endl;
    }

    std::cout << "data1.value = " << data1.value() << std::endl;
    std::cout << "data1.value = " << *data1 << std::endl;

    std::cout << "data2.value = " << data2.value_or(0) << std::endl;

    return 0;
}

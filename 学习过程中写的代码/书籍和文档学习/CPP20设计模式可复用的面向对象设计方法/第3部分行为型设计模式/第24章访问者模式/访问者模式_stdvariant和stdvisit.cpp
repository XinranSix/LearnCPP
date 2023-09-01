#include <iostream>
#include <string>
#include <type_traits>
#include <variant>

struct AddressPrinter {
    void operator()(std::string const &house_name) const {
        std::cout << "A house called " << house_name << "\n";
    }

    void operator()(int house_number) const {
        std::cout << "House number " << house_number << "\n";
    }
};

int main(int argc, char *argv[]) {

    std::variant<std::string, int> house;
    house = "Montefiore Castle";
    house = 221;

    AddressPrinter ap;
    std::visit(ap, house);

    std::visit(
        [](auto &arg) {
            using T = std::decay_t<decltype(arg)>;

            if constexpr (std::is_same_v<T, std::string>) {
                std::cout << "A house called " << arg.c_str() << "\n";
            } else {
                std::cout << "House number " << arg << "\n";
            }
        },
        house);

    return 0;
}

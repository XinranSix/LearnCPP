#include <compare>
#include <iostream>

int main(int arvc, char *argv[]) {

    int i{11};
    std::strong_ordering result{i <=> 0};

    if (result == std::strong_ordering::less) {
        std::cout << "less" << std::endl;
    }
    if (result == std::strong_ordering::greater) {
        std::cout << "greater" << std::endl;
    }
    if (result == std::strong_ordering::equal) {
        std::cout << "equal" << std::endl;
    }

    if (std::is_lt(result)) {
        std::cout << "less" << std::endl;
    }
    if (std::is_gt(result)) {
        std::cout << "greater" << std::endl;
    }
    if (std::is_eq(result)) {
        std::cout << "equal" << std::endl;
    }

    return 0;
}

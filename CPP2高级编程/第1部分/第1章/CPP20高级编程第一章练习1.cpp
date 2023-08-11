#include <iostream>

namespace HR {
    struct Employee {
        char firstInitial;
        char lastInitial;
        int employeeNumber;
        int salary;
    };
} // namespace HR

int main(int arvc, char *argv[]) {

    HR::Employee emp{.firstInitial = 'h',
                     .lastInitial = 't',
                     .employeeNumber = 114514,
                     .salary = 123312};

    return 0;
}

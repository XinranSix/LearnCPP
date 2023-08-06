#include <iostream>

namespace HR {

    enum class Title { Manage, SeniorEngineer, Engineer };

    struct Employee {
        char firstInitial;
        char lastInitial;
        int employeeNumber;
        int salary;
        Title title;
    };
} // namespace HR

int main(int arvc, char *argv[]) {

    HR::Employee emp{.firstInitial = 'h',
                     .lastInitial = 't',
                     .employeeNumber = 114514,
                     .salary = 123312,
                     .title = HR::Title::Manage};

    switch (emp.title) {
    case HR::Title::Manage:
        std::cout << "Manage" << std::endl;
        break;
    case HR::Title::SeniorEngineer:
        std::cout << "SeniorEngineer" << std::endl;
        break;
    case HR::Title::Engineer:
        std::cout << "Engineer" << std::endl;
        break;
    default:
        std::cout << "Unknown" << std::endl;
        break;
    }

    return 0;
}

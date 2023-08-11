#include <array>
#include <iostream>
#include <format>

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

void printEmployee(HR::Employee const &employee) {

    std::cout << std::format("Name : {} {}", employee.firstInitial,
                             employee.lastInitial)
              << std::endl;
    std::cout << std::format("Employee Number: {}", employee.employeeNumber)
              << std::endl;
    std::cout << std::format("Employee salary: {}", employee.salary)
              << std::endl;
    std::cout << "Employee title: ";

    switch (employee.title) {
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
}

int main(int arvc, char *argv[]) {

    HR::Employee emp1{.firstInitial = 'h',
                      .lastInitial = 't',
                      .employeeNumber = 114514,
                      .salary = 123312,
                      .title = HR::Title::Manage};

    HR::Employee emp2{.firstInitial = 'y',
                      .lastInitial = 'j',
                      .employeeNumber = 1231,
                      .salary = 3242,
                      .title = HR::Title::SeniorEngineer};

    HR::Employee emp3{.firstInitial = 'x',
                      .lastInitial = 'j',
                      .employeeNumber = 234,
                      .salary = 13412,
                      .title = HR::Title::Engineer};

    std::array<HR::Employee, 3> employees{emp1, emp2, emp3};

    for (const auto &employee : employees) {
        printEmployee(employee);
    }

    return 0;
}

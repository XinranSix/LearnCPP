#include <format>
#include <iostream>

struct Employee {
    char firstInitial;
    char lastInitial;
    int employeeNumber;
    int salary;
};

int main(int arvc, char *argv[]) {

    Employee anEmployee;

    anEmployee.firstInitial = 'J';
    anEmployee.lastInitial = 'D';
    anEmployee.employeeNumber = 42;
    anEmployee.salary = 80000;

    std::cout << std::format("Employee: {}{}", anEmployee.firstInitial,
                             anEmployee.lastInitial)
              << std::endl;
    std::cout << std::format("Number: {}", anEmployee.employeeNumber)
              << std::endl;
    std::cout << std::format("Salary: ${}", anEmployee.salary) << std::endl;

    return 0;
}

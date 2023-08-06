#include <iostream>
#include <array>
#include <format>
#include <stdexcept>
#include <vector>
#include <compare>
#include <utility>
#include <optional>
#include <exception>

/* -------------------------------- Employee -------------------------------- */

namespace Records {
    const int DefaultStartingSalary{30'000};
    const int DefaultRaiseAndDemeritAmount{1'000};

    class Employee {
    public:
        Employee(std::string const &firstName, std::string const &lastName);

        void promote(int raiseAmount = DefaultRaiseAndDemeritAmount); // 升职
        void demote(int demerit = DefaultRaiseAndDemeritAmount);      // 降职
        void hire();                                                  // 雇佣
        void fire();          // 炒鱿鱼
        void display() const; // 显示

        // 各种 setter 和 getter
        void setFirstName(std::string const &firstName);
        std::string const &getFirstName() const;

        void setLastName(std::string const &lastName);
        std::string const &getLastName() const;

        void setEmployeeNumber(int employeeNumber);
        int getEmployeeNumber() const;

        void setSalary(int newSalary);
        int getSalary() const;

        bool isHired() const;

    private:
        std::string m_firstName;
        std::string m_lastName;
        int m_employeeNumber{-1};
        int m_salary{DefaultStartingSalary};
        bool m_hired{false};
    };
}; // namespace Records

namespace Records {

    Employee::Employee(std::string const &firstName,
                       std::string const &lastName)
        : m_firstName{firstName}, m_lastName{lastName} {}

    void Employee::promote(int raiseAmount) {
        setSalary(getSalary() + raiseAmount);
    }

    void Employee::demote(int demerit) { setSalary(getSalary() - demerit); }

    void Employee::hire() { m_hired = true; }

    void Employee::fire() { m_hired = false; }

    void Employee::display() const {
        using namespace std;
        cout << format("Employee: {}, {}", getLastName(), getFirstName())
             << endl;
        cout << "------------------------------" << endl;
        cout << (isHired() ? "Current Employee" : "Former Employee") << endl;
        cout << format("Employee Number: {}", getEmployeeNumber()) << endl;
        cout << format("Salary: ${}", getSalary()) << endl;
        cout << endl;
    }

    void Employee::setFirstName(std::string const &firstName) {
        m_firstName = firstName;
    }

    std::string const &Employee::getFirstName() const { return m_firstName; }

    void Employee::setLastName(std::string const &lastName) {
        m_lastName = lastName;
    }

    std::string const &Employee::getLastName() const { return m_lastName; }

    void Employee::setEmployeeNumber(int employeeNumber) {
        m_employeeNumber = employeeNumber;
    }

    int Employee::getEmployeeNumber() const { return m_employeeNumber; }

    void Employee::setSalary(int newSalary) { m_salary = newSalary; }

    int Employee::getSalary() const { return m_salary; }

    bool Employee::isHired() const { return m_hired; }

}; // namespace Records

void employeeTest() {
    using namespace std;
    using namespace Records;

    std::cout << "Testing the Employee class." << std::endl;
    Employee emp{"Jane", "Doe"};
    emp.setFirstName("John");
    emp.setLastName("Doe");
    emp.setEmployeeNumber(71);
    emp.setSalary(50'000);
    emp.promote();
    emp.promote(50);
    emp.hire();
    emp.display();
}

/* -------------------------------- Database -------------------------------- */

namespace Records {
    const int FirstEmployeeNumber{1'000};

    class Database {
    public:
        Employee &addEmployee(std::string const &firstName,
                              std::string const &lastName);

        Employee &getEmployee(int employeeNumber);

        Employee &getEmployee(std::string const &firstName,
                              std::string const &lastName);

        void displayAll() const;
        void displayCurrent() const;
        void displayFormer() const;

    private:
        std::vector<Employee> m_employees;
        int m_nextEmployeeNumber{FirstEmployeeNumber};
    };
}; // namespace Records

namespace Records {

    Employee &Database::addEmployee(std::string const &firstName,
                                    std::string const &lastName) {
        Employee theEmployee{firstName, lastName};
        theEmployee.setEmployeeNumber(m_nextEmployeeNumber++);
        theEmployee.hire();
        m_employees.push_back(theEmployee);
        return m_employees.back();
    }

    Employee &Database::getEmployee(int employeeNumber) {
        for (auto &employee : m_employees) {
            if (employee.getEmployeeNumber() == employeeNumber) {
                return employee;
            }
        }
        throw std::logic_error{"No employee found."};
    }

    Employee &Database::getEmployee(std::string const &firstName,
                                    std::string const &lastName) {
        for (auto &employee : m_employees) {
            if (employee.getFirstName() == firstName &&
                employee.getLastName() == lastName) {
                return employee;
            }
        }
        throw std::logic_error{"No employee found."};
    }

    void Database::displayAll() const {
        for (const auto &employee : m_employees) {
            employee.display();
        }
    }

    void Database::displayCurrent() const {
        for (const auto &employee : m_employees) {
            if (employee.isHired()) {
                employee.display();
            }
        }
    }

    void Database::displayFormer() const {
        for (const auto &employee : m_employees) {
            if (!employee.isHired()) {
                employee.display();
            }
        }
    }

}; // namespace Records

void databaseTest() {

    using namespace std;
    using namespace Records;

    Database myDB;

    Employee &emp1{myDB.addEmployee("Greg", "Wallis")};
    emp1.fire();

    Employee &emp2{myDB.addEmployee("Marc", "White")};
    emp2.setSalary(100'000);

    Employee &emp3{myDB.addEmployee("John", "Doe")};
    emp3.setSalary(10'000);
    emp3.promote();

    cout << "all employess: " << endl << endl;
    myDB.displayAll();

    cout << "current employess: " << endl << endl;
    myDB.displayCurrent();

    cout << "former employess: " << endl << endl;
    myDB.displayFormer();
}

/* ------------------------------ UserInterface ----------------------------- */

using namespace std;
using namespace Records;

int displayMenu();
void diHire(Database &db);
void diFire(Database &db);
void diPromote(Database &db);

int main(int arvc, char *argv[]) {

    // employeeTest();
    // databaseTest();

    Database employeeDB;
    bool done{false};
    while (!done) {
        int selection{displayMenu()};
        switch (selection) {
        case 0:
            done = true;
            break;
        case 1:
            diHire(employeeDB);
            break;
        case 2:
            diFire(employeeDB);
            break;
        case 3:
            diPromote(employeeDB);
            break;
        case 4:
            employeeDB.displayAll();
            break;
        case 5:
            employeeDB.displayFormer();
            break;
        default:
            cerr << "Unknown command." << endl;
            break;
        }
    }

    return 0;
}

int displayMenu() {
    int selection{};

    cout << endl;
    cout << "Employee Database" << endl;
    cout << "-----------------" << endl;
    cout << "1) Hire a new employee" << endl;
    cout << "2) Fire an employee" << endl;
    cout << "3) Promote an employee" << endl;
    cout << "4) List all employess" << endl;
    cout << "5) List all current employess" << endl;
    cout << "6) List all former employess" << endl;
    cout << "0) Quit" << endl;
    cout << endl;
    cout << "--->";
    cin >> selection;

    return selection;
}

void diHire(Database &db) {
    string firstName;
    string lastName;

    cout << "First name? ";
    cin >> firstName;

    cout << "Last name? ";
    cin >> lastName;

    auto &employee{db.addEmployee(firstName, lastName)};
    cout << format("Hired employee {} {} with employee number {}.", firstName,
                   lastName, employee.getEmployeeNumber())
         << endl;
}

void diFire(Database &db) {

    int employeeNumber{};
    cout << "Employee number? ";
    cin >> employeeNumber;

    try {
        auto &emp{db.getEmployee(employeeNumber)};
        emp.fire();
        cout << format("Employee {} terminated", employeeNumber) << endl;
    } catch (const std::logic_error &e) {
        cerr << format("Unable to terminate employee: {}", e.what()) << endl;
    }
}

void diPromote(Database &db) {

    int employeeNumber{};
    cout << "Employee number? ";
    cin >> employeeNumber;

    int raiseAmount;
    cout << "How much of a raise? ";
    cin >> raiseAmount;

    try {
    } catch (std::logic_error const &e) {
        cerr << format("Unable to promote employee: {}", e.what()) << endl;
    }
}

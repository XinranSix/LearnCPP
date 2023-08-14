#include <format>
#include <iostream>
#include <memory>
#include <utility>
#include <vector>

namespace HR {
    class Person {
    public:
        Person() = default;

        Person(std::string const &firstName, std::string const &lastName)
            : Person { firstName, lastName,
                       std::format("{}{}", firstName[0], lastName[0]) } {
        }

        Person(std::string const &firstName, std::string const &lastName,
               std::string const &initials)
            : m_firstName { firstName }, m_lastName { lastName },
              m_initials { initials } {
        }

        virtual ~Person() = default;

    public:
        [[nodiscard]] auto operator<=>(Person const &) const = default;

    public:
        virtual std::string const &getFirstName() const {
            return m_firstName;
        }
        virtual void setFirstName(std::string const &firstName) {
            m_firstName = firstName;
        }

        virtual std::string const &getLastName() const {
            return m_lastName;
        }
        virtual void setLastName(std::string const &lastName) {
            m_lastName = lastName;
        }

        virtual std::string const &getInitials() const {
            return m_initials;
        }

        virtual void setInitials(std::string const &initials) {
            m_initials = initials;
        }

        virtual std::string toString() const = 0;

    private:
        std::string m_firstName;
        std::string m_lastName;
        std::string m_initials;
    };
}; // namespace HR

namespace HR {
    class Employee : public Person {
    public:
        Employee() = default;

        Employee(std::string const &firstName, std::string const &lastName)
            : Employee { std::move(firstName), std::move(lastName),
                         std::format("{}{}", firstName[0], lastName[0]) } {
        }

        Employee(std::string const &firstName, std::string const &lastName,
                 std::string const &initials)
            : Employee { std::move(firstName), std::move(lastName),
                         std::move(initials), 0 } {
        }

        Employee(std::string const &firstName, std::string const &lastName,
                 std::string const &initials, size_t employeeID)
            : Person { firstName, lastName, initials },
              m_employeeID { std::exchange(employeeID, 0) } {
        }

    public:
        virtual size_t getEmployeeId() const {
            return m_employeeID;
        }
        virtual void setEmployeeId(size_t employeeId) {
            m_employeeID = employeeId;
        }

        std::string toString() const override {
            return std::format("Employee:\nFirstName: {}\nLastName: "
                               "{}\nInitials: {}\nEmployeeId: {}",
                               getFirstName(), getLastName(), getInitials(),
                               getEmployeeId());
        }

    private:
        size_t m_employeeID {};
    };
}; // namespace HR

namespace HR {
    class Manager : public Employee {
    public:
        using Employee::Employee;

        std::string toString() const override {
            return std::format("Manager:\nFirstName: {}\nLastName: "
                               "{}\nInitials: {}\nEmployeeId: {}",
                               getFirstName(), getLastName(), getInitials(),
                               getEmployeeId());
        }
    };
}; // namespace HR

namespace HR {
    class Director : public Employee {
    public:
        using Employee::Employee;

        std::string toString() const override {
            return std::format("Director:\nFirstName: {}\nLastName: "
                               "{}\nInitials: {}\nEmployeeId: {}",
                               getFirstName(), getLastName(), getInitials(),
                               getEmployeeId());
        }
    };
}; // namespace HR

int main(int argc, char *argv[]) {

    std::vector<std::unique_ptr<HR::Person>> people;

    people.push_back(std::make_unique<HR::Employee>("Y", "J"));
    people.push_back(std::make_unique<HR::Manager>("H", "YT"));
    people.push_back(std::make_unique<HR::Director>("H", "Y"));

    for (auto const &person : people) {
        std::cout << person->toString() << std::endl << std::endl;
    }

    return 0;
}

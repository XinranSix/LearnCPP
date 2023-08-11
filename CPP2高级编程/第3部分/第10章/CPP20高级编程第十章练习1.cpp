#include <format>
#include <iostream>
#include <memory>
#include <utility>

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

    private:
        std::string m_firstName;
        std::string m_lastName;
        std::string m_initials;
    };
}; // namespace HR

namespace HR {
    class Employee : Person {

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

        ~Employee() = default;

    public:
        virtual size_t getEmployeeId() const {
            return m_employeeID;
        }
        virtual void setEmployeeId(size_t employeeId) {
            m_employeeID = employeeId;
        }

    private:
        size_t m_employeeID;
    };
}; // namespace HR

namespace HR {
    class Manager : public Employee {
    public:
        ~Manager() = default;
    };
}; // namespace HR

namespace HR {
    class Director : public Employee {
    public:
        ~Director() = default;
    };
}; // namespace HR

namespace HR {};

int main(int argc, char *argv[]) {

    return 0;
}

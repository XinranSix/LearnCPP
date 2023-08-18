#include <format>
#include <iostream>
#include <memory>

class Person {

public:
    Person() {
    }

    Person(std::string const &firstName, std::string const &lastName)
        : Person { firstName, lastName,
                   std::format("{}{}", firstName[0], lastName[0]) } {
    }

    Person(std::string const &firstName, std::string const &lastName,
           std::string const &initials)
        : m_firstName { firstName }, m_lastName { lastName },
          m_initials { initials } {
    }

    ~Person() {
    }

public:
    std::string const &getFirstName() const {
        return m_firstName;
    }
    void setFirstName(std::string const &firstName) {
        m_firstName = firstName;
    }

    std::string const &getLastName() const {
        return m_lastName;
    }
    void setLastName(std::string const &lastName) {
        m_lastName = lastName;
    }

    std::string const &getInitials() const {
        return m_initials;
    }
    void setInitials(std::string const &initials) {
        m_initials = initials;
    }

private:
    std::string m_firstName;
    std::string m_lastName;
    std::string m_initials;
};

bool operator==(Person const &p1, Person const &p2) {
    return p1.getFirstName() == p2.getFirstName() ||
           p1.getLastName() == p2.getLastName();
}

bool operator!=(Person const &p1, Person const &p2) {
    return !(p1 == p2);
}

bool operator<(Person const &p1, Person const &p2) {
    if (p1.getFirstName() < p2.getFirstName()) {
        return true;
    }
    if (p1.getFirstName() > p2.getFirstName()) {
        return false;
    }
    if (p1.getLastName() < p2.getLastName()) {
        return true;
    }
    if (p1.getLastName() > p2.getLastName()) {
        return false;
    }
    if (p1.getInitials() < p2.getInitials()) {
        return true;
    }
    return false;
}

bool operator>(Person const &p1, Person const &p2) {
    if (p1.getFirstName() > p2.getFirstName()) {
        return true;
    }
    if (p1.getLastName() < p2.getLastName()) {
        return false;
    }
    if (p1.getLastName() > p2.getLastName()) {
        return true;
    }
    if (p1.getLastName() < p2.getLastName()) {
        return false;
    }
    if (p1.getInitials() > p2.getInitials()) {
        return true;
    }
    return false;
}

bool operator<=(Person const &p1, Person const &p2) {
    return !(p1 > p2);
}

bool operator>=(Person const &p1, Person const &p2) {
    return !(p1 < p2);
}

int main(int argc, char *argv[]) {

    using namespace std;

    Person person { "John", "Doe" };
    cout << format("The initials of {} {} are {}.", person.getFirstName(),
                   person.getLastName(), person.getInitials())
         << endl;

    Person person2 { "Marc", "Gregoire", "Mg" };
    cout << format("The initials of {} {} are {}.", person2.getFirstName(),
                   person2.getLastName(), person2.getInitials())
         << endl;

    Person persons[3];

    // Test copy constructor.
    Person copy { person };

    // Test assignment operator.
    Person otherPerson { "Jane", "Doe" };
    copy = otherPerson;

    // Test comparison operators.
    if (person < person2) {
        cout << "person < person2" << endl;
    }
    if (person > person2) {
        cout << "person > person2" << endl;
    }
    if (person <= person2) {
        cout << "person <= person2" << endl;
    }
    if (person >= person2) {
        cout << "person >= person2" << endl;
    }
    if (person == person2) {
        cout << "person == person2" << endl;
    }
    if (person != person2) {
        cout << "person != person2" << endl;
    }

    return 0;
}

//// The ordering of Persons depends on the order of the data members
//// in the Person class definition. In the above implementation, Persons
//// are ordered on first name, then on last name, then on initials.
//// If instead you want to order them first on last name, then first name
//// then initials, you have to rearrange the data members as follows:
////	private:
////		std::string m_lastName;
////		std::string m_firstName;
////		std::string m_initials;

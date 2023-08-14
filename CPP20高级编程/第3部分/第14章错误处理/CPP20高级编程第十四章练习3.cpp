#include <iomanip>
#include <ios>
#include <iostream>
#include <filesystem>
#include <format>
#include <stdexcept>
#include <string>
#include <ostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string_view>

class Person {

public:
    Person() {}

    Person(std::string const &firstName, std::string const &lastName)
        : Person { firstName, lastName,
                   std::format("{}{}", firstName[0], lastName[0]) } {}

    Person(std::string const &firstName, std::string const &lastName,
           std::string const &initials)
        : m_firstName { firstName }, m_lastName { lastName },
          m_initials { initials } {}

    ~Person() {}

public:
    [[nodiscard]] auto operator<=>(Person const &) const = default;
    // [[nodiscard]] bool operator==(Person const &) const = default;

public:
    void output(std::ostream &os) const {

        os << std::format("{}{} {}", m_firstName, m_lastName, m_initials)
           << std::endl;
    }

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

class Database {
public:
    void add(Person person);

    void clear();

    void save(std::string_view filename) const;

    void load(std::string_view filename);

    void outputAll(std::ostream &output) const;

private:
    std::vector<Person> m_persons;
};

void Database::add(Person person) {
    m_persons.push_back(std::move(person));
}

void Database::clear() {
    m_persons.clear();
}

void Database::save(std::string_view filename) const {
    std::ofstream ofs { filename.data(), std::ios_base::trunc };
    if (!ofs) {
        throw std::runtime_error { "打开文件失败" };
        return;
    }
    for (auto const &person : m_persons) {
        ofs << std::quoted(person.getFirstName())
            << std::quoted(person.getLastName())
            << std::quoted(person.getInitials()) << std::endl;
        if (!ofs) {
            throw std::runtime_error { "Failed to write person to file." };
        }
    }
}

void Database::load(std::string_view filename) {
    std::ifstream ifs { filename.data() };
    if (!ifs) {
        throw std::runtime_error { "打开文件失败" };
    }
    while (ifs) {
        std::string line;
        std::getline(ifs, line);
        if (!ifs && !ifs.eof()) {
            throw std::runtime_error { "Failed to read line from file." };
        }
        if (line.empty()) {
            continue;
        }
        std::string firstName, lastName, initials;
        std::istringstream iss { line };
        iss >> std::quoted(firstName) >> std::quoted(lastName) >>
            std::quoted(initials);
        if (iss.bad()) {
            std::cerr << "Error reading person. Ignoring." << std::endl;
            continue;
        }
        m_persons.push_back(Person { std::move(firstName), std::move(lastName),
                                     std::move(initials) });
    }
}

void Database::outputAll(std::ostream &os) const {
    for (auto const &person : m_persons) {
        person.output(os);
    }
}

int main(int argc, char *argv[]) {
    // Fill a database.
    Database db;
    db.add(Person { "John", "Doe" });
    db.add(Person { "Marc", "Gregoire", "Mg" });
    db.add(Person { "Peter", "Van Weert", "PVW" });

    // Output all persons in the database to standard output.
    std::cout << "Initial database contents:" << std::endl;
    db.outputAll(std::cout);

    // Save the database to a file.
    db.save("person.db");

    // Clear the database.
    db.clear();
    std::cout << "\nDatabase contents after clearing:" << std::endl;
    db.outputAll(std::cout);

    // Load database from file.
    std::cout << "\nLoading database from file..." << std::endl;
    db.load("person.db");
    std::cout << "\nDatabase contents after loading from file:" << std::endl;
    db.outputAll(std::cout);

    return 0;
}

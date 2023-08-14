#include <iomanip>
#include <ios>
#include <iostream>
#include <filesystem>
#include <format>
#include <string>
#include <ostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string_view>

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

    void save(std::filesystem::path const &path) const;

    void load(std::filesystem::path const &path);

    void outputAll(std::ostream &output) const;

private:
    void loadFile(std::filesystem::path const &path);

private:
    std::vector<Person> m_persons;
};

void Database::add(Person person) {
    m_persons.push_back(std::move(person));
}

void Database::clear() {
    m_persons.clear();
}

void Database::save(std::filesystem::path const &path) const {

    for (auto const &person : m_persons) {
        std::filesystem::path filename { path };
        filename /= person.getInitials();
        filename += ".person";

        std::ofstream ofs { filename, std::ios_base::trunc };
        if (!ofs) {
            std::cerr << "打开文件失败" << std::endl;
            return;
        }
        ofs << std::quoted(person.getFirstName())
            << std::quoted(person.getLastName())
            << std::quoted(person.getInitials()) << std::endl;
    }
}

void Database::load(std::filesystem::path const &path) {
    std::filesystem::directory_iterator begin { path }, end {};
    for (auto iter { begin }; iter != end; ++iter) {
        decltype(auto) entry { *iter };
        if (!entry.path().has_extension() ||
            entry.path().extension() != ".person") {
            continue;
        }
        loadFile(entry);
    }
}

void Database::outputAll(std::ostream &os) const {
    for (auto const &person : m_persons) {
        person.output(os);
    }
}

void Database::loadFile(std::filesystem::path const &path) {
    std::ifstream ifs { path };
    if (!ifs) {
        std::cout << "文件打开失败" << std::endl;
        return;
    }

    while (ifs) {
        std::string line;
        std::getline(ifs, line);
        if (line.empty()) {
            continue;
        }
        std::istringstream iss { line };
        std::string firstName, lastName, initials;
        iss >> std::quoted(firstName) >> std::quoted(lastName) >>
            std::quoted(initials);
        if (iss.bad()) {
            continue;
        }
        m_persons.push_back(Person { std::move(firstName), std::move(lastName),
                                     std::move(initials) });
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

    // Save the database to files.
    db.save("./");

    // Clear the database.
    db.clear();
    std::cout << "\nDatabase contents after clearing:" << std::endl;
    db.outputAll(std::cout);

    // Load database from files.
    std::cout << "\nLoading database from files..." << std::endl;
    db.load("./");
    std::cout << "\nDatabase contents after loading from files:" << std::endl;
    db.outputAll(std::cout);

    return 0;
}

#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

class person_t {
public:
    enum gender_t { female, male, other };

    enum output_format_t { name_only, full_name };

    person_t() : m_name("John"), m_surname("Doe"), m_gender(other) {}

    person_t(std::string name, gender_t gender, int age = 0)
        : m_name(name), m_surname("Doe"), m_gender(gender), m_age(age) {}

    person_t(std::string name, const std::string &surname, gender_t gender, int age = 0)
        : m_name(name), m_surname(surname), m_gender(gender), m_age(age) {}

    std::string name() const {
        return m_name;
    }

    std::string surname() const {
        return m_surname;
    }

    gender_t gender() const {
        return m_gender;
    }

    int age() const {
        return m_age;
    }

    void print(std::ostream &out, person_t::output_format_t format) const {
        if (format == person_t::name_only) {
            out << name() << '\n';

        } else if (format == person_t::full_name) {
            out << name() << ' ' << surname() << '\n';
        }
    }

private:
    std::string m_name;
    std::string m_surname;
    gender_t m_gender;
    int m_age;
};

void print_person(person_t const &person, std::ostream &out, person_t::output_format_t format) {
    if (format == person_t::name_only) {
        out << person.name() << '\n';
    } else if (format == person_t::full_name) {
        out << person.name() << ' ' << person.surname() << '\n';
    }
}

int main(int argc, char *argv[]) {

    std::vector<int> scores {};

    using namespace std::placeholders;
    std::sort(begin(scores), end(scores), std::bind(std::greater<> {}, _2, _1));

    return 0;
}

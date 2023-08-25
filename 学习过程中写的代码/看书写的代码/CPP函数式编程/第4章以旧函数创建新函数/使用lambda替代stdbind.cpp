#include "fmt/core.h"
#include <functional>
#include <vector>
#include <algorithm>
#include <iostream>
#include <ostream>

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

    std::vector<person_t> people { { "David", person_t::male },    { "Jane", person_t::female },
                                   { "Martha", person_t::female }, { "Peter", person_t::male },
                                   { "Rose", person_t::female },   { "Tom", person_t::male } };

    auto bound { []() { return std::greater<> {}(6, 42); } };

    auto is_greater_than_42 { [](double value) { return std::greater<> {}(value, 42); } };
    auto is_less_than_42 { [](double value) { return std::greater<> {}(42, value); } };

    fmt::print("{}\n", is_less_than_42(6));
    fmt::print("{}\n", is_greater_than_42(6));

    std::vector<int> scores {};

    std::sort(begin(scores), end(scores),
              [](double value1, double value2) { return std::greater<> {}(value2, value1); });

    std::for_each(cbegin(people), cend(people),
                  [](auto const &person) { print_person(person, std::cout, person_t::name_only); });

    return 0;
}

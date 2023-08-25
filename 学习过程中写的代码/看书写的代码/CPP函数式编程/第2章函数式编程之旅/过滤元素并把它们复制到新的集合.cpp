#include <algorithm>
#include <iterator>
#include <pstl/glue_algorithm_defs.h>
#include <string>
#include <vector>
#include <iostream>

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

std::string name(const person_t &person) {
    return person.name();
}

bool is_female(const person_t &person) {
    return person.gender() == person_t::female;
}

bool is_not_female(const person_t &person) {
    return !is_female(person);
}

int main(int argc, char *argv[]) {

    std::vector<person_t> people { { "David", person_t::male },    { "Jane", person_t::female },
                                   { "Martha", person_t::female }, { "Peter", person_t::male },
                                   { "Rose", person_t::female },   { "Tom", person_t::male } };

    std::vector<person_t> females;
    std::vector<std::string> names(females.size());

    std::copy_if(cbegin(people), cend(people), std::back_inserter(females), is_female);
    std::transform(cbegin(females), cend(females), names.begin(), name);

    return 0;
}

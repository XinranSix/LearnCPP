#include <iostream>
#include <string>
#include <utility>
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

std::string name(const person_t &person) {
    return person.name();
}

bool is_female(const person_t &person) {
    return person.gender() == person_t::female;
}

bool is_not_female(const person_t &person) {
    return !is_female(person);
}

template <typename FilterFunction, typename Iterator>
    requires requires(FilterFunction ff) {
        ff(); /*限定为可调用对象*/
    }
std::vector<std::string> names_for_helper(Iterator people_begin, Iterator people_end,
                                          FilterFunction filter,
                                          std::vector<std::string> previously_collected) {
    if (people_begin == people_end) {
        return previously_collected;
    } else {
        const auto head = *people_begin;
        if (filter(head)) {
            previously_collected.push_back(name(head));
        }
        return names_for_helper(people_begin + 1, people_end, filter,
                                std::move(previously_collected));
    }
}

template <typename FilterFunction, typename Iterator>
    requires requires(FilterFunction ff) {
        ff(); /*限定为可调用对象*/
    }
std::vector<std::string> names_for(Iterator people_begin, Iterator people_end,
                                   FilterFunction filter) {
    return names_for_helper(people_begin, people_end, filter, {});
}

int main(int argc, char *argv[]) {

    std::vector<person_t> people { { "David", person_t::male },    { "Jane", person_t::female },
                                   { "Martha", person_t::female }, { "Peter", person_t::male },
                                   { "Rose", person_t::female },   { "Tom", person_t::male } };

    return 0;
}

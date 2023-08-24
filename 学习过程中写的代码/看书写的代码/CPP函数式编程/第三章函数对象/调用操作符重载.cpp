#include <algorithm>
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

class older_than {
public:
    older_than(int limit) : m_limit { limit } {}

    bool operator()(person_t const &person) const {
        return person.age() > m_limit;
    }

private:
    int m_limit {};
};

int main(int argc, char *argv[]) {

    person_t person {};
    std::vector<person_t> persons {};

    older_than older_than_42 { 42 };
    older_than older_than_14 { 14 };

    if (older_than_42(person)) {
        std::cout << person.name() << " is more than 42 years old\n";
    } else if (older_than_14(person)) {
        std::cout << person.name() << " is more than 14 years old\n";
    } else {
        std::cout << person.name() << " is 14 years old, or younger\n";
    }

    std::count_if(cbegin(persons), cend(persons), older_than { 42 });
    std::count_if(cbegin(persons), cend(persons), older_than { 16 });

    return 0;
}

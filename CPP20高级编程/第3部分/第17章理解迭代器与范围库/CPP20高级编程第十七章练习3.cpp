#include <format>
#include <iostream>
#include <iterator>
#include <utility>
#include <vector>
#include <ranges>
#include <ostream>
#include <iterator>

class Person {
public:
    Person(std::string first, std::string last) : m_firstName { first }, m_lastName { last } {}

    std::string const &getFirstName() const {
        return m_firstName;
    }

    std::string const &getLastName() const {
        return m_lastName;
    }

private:
    std::string m_firstName;
    std::string m_lastName;
};

std::ostream &operator<<(std::ostream &os, Person const &person) {
    return os << std::format("{} {}", person.getFirstName(), person.getLastName());
}

template <typename InputIter, typename OutputIter>
void myCopy(InputIter begin, InputIter end, OutputIter target) {
    for (auto iter { begin }; iter != end; ++iter, ++target) {
        *target = *iter;
    }
}

int main(int argc, char *argv[]) {

    std::vector<std::pair<Person, size_t>> persons {
        std::pair { Person { "Izzie", "Fellows" }, 11 },
        std::pair { Person { "Eshaan", "Cooper" }, 15 },
        std::pair { Person { "Rick", "Crouch" }, 48 },
        std::pair { Person { "Faye", "Pittman" }, 35 },
        std::pair { Person { "Jude", "Bone" }, 69 },
        std::pair { Person { "Ella-Louise", "Byers" }, 60 },
        std::pair { Person { "Jad", "Lott" }, 75 },
        std::pair { Person { "Teddie", "Love" }, 24 },
        std::pair { Person { "Niko", "Silva" }, 16 },
        std::pair { Person { "Bryan", "Melendez" }, 42 }
    };

    auto result { std::views::common(persons | std::views::keys | std::views::take(4)) };

    myCopy(begin(result), end(result), std::ostream_iterator<Person> { std::cout, "\n" });

    auto result1 { std::views::common(
        result | std::views::transform([](auto const &person) { return person.getLastName(); })) };

    std::cout << std::endl;

    myCopy(begin(result1), end(result1), std::ostream_iterator<std::string> { std::cout, "\n" });

    return 0;
}

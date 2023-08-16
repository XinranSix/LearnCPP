#include <iostream>
#include <iterator>
#include <utility>
#include <vector>
#include <ranges>

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

template <typename InputIter>
auto sum(InputIter begin, InputIter end) {
    auto sum { *begin };
    for (auto iter { ++begin }; iter != end; ++iter) {
        sum += *iter;
    }
    return sum;
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

    auto result(
        std::views::common(persons | std::views::values |
                           std::views::filter([](auto const &v) { return v >= 12 && v < 65; })));

    auto count { std::distance(begin(result), end(result)) };
    auto avg { sum(begin(result), end(result)) / static_cast<double>(count) };
    std::cout << avg << std::endl;

    return 0;
}

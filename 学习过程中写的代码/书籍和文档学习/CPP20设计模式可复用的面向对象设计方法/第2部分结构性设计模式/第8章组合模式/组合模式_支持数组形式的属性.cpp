#include <algorithm>
#include <array>
#include <iostream>
#include <numeric>

// MARK: 不错的设计
class Creature {
    enum Abilties { str, agl, intl, count };
    std::array<int, count> abilties;

    int strength, agility, intelligence;

public:
    int get_strength() const { return abilties[str]; }
    void set_strength(int strength) { abilties[str] = strength; }

    int get_agility() const { return abilties[agl]; }
    void set_agility(int agility) { abilties[agl] = agility; }

    int get_intelligence() const { return abilties[intl]; }
    void set_intelligence(int intelligence) { abilties[intl] = intelligence; }

    int sum() const {
        return std::accumulate(begin(abilties), end(abilties), 0);
    }

    double average() const { return sum() / (double)count; }

    int max() const {
        return *std::max_element(begin(abilties), end(abilties));
    }
};

int main(int argc, char *argv[]) { return 0; }

#include <iostream>

enum class CreatureAbility { strength, agility };

struct CreatureCommand {
    enum Action { set, increaseBy, decreaseBy } action;

    CreatureAbility ability;
    int amount {};
};

struct CreatureQuery {
    CreatureAbility ability;
};

class Creature {
    int strength {};
    int agility {};

public:
    Creature(int strength, int agility)
        : strength { strength }, agility { agility } {}

    void process_command(CreatureCommand const &cc);
    int process_query(CreatureQuery const &q) const;

    void set_strength(int value);

    int get_strength() const;

    void set_agility(int value);

    int get_agility() const;
};

void Creature::process_command(CreatureCommand const &cc) {
    int *ability;
    switch (cc.ability) {
    case CreatureAbility::strength:
        ability = &strength;
        break;
    case CreatureAbility::agility:
        ability = &agility;
        break;
    }
    switch (cc.action) {
    case CreatureCommand::set:
        *ability = cc.amount;
        break;
    case CreatureCommand::increaseBy:
        *ability += cc.amount;
        break;
    case CreatureCommand::decreaseBy:
        *ability -= cc.amount;
        break;
    }
}

int Creature::process_query(CreatureQuery const &q) const {
    switch (q.ability) {
    case CreatureAbility::strength:
        return strength;
    case CreatureAbility::agility:
        return agility;
    }
    return 0;
}

void Creature::set_strength(int value) {
    process_command(CreatureCommand { CreatureCommand::set,
                                      CreatureAbility::strength, value });
}

int Creature::get_strength() const {
    return process_query(CreatureQuery { CreatureAbility::strength });
}

void Creature::set_agility(int value) {
    process_command(CreatureCommand { CreatureCommand::set,
                                      CreatureAbility::agility, value });
}

int Creature::get_agility() const {
    return process_query(CreatureQuery { CreatureAbility::agility });
}

int main(int argc, char *argv[]) { return 0; }

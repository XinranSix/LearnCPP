#include "boost/signals2.hpp"
#include "boost/signals2/connection.hpp"
#include <format>
#include <iostream>
#include <ostream>
#include <string>
#include <utility>

struct Query {
    std::string creature_name;
    enum Argument { attack, defense } argument;
    int result;
};

struct Game {
    boost::signals2::signal<void(Query &)> queries;
};

class Creature {
    Game &game;
    int attack, defence;

public:
    std::string name;

    Creature(Game &game, std::string name, int attack, int defence)
        : game { game }, name { std::move(name) }, attack { attack },
          defence { defence } {}

    friend std::ostream &operator<<(std::ostream &os,
                                    Creature const &creature) {
        return os << std::format("name: {} attack: {} defense: {}",
                                 creature.name, creature.attack,
                                 creature.defence);
    }

    int get_attack() const {
        Query q { name, Query::Argument::attack, attack };
        game.queries(q);
        return q.result;
    }
    void set_attack(int attack) { this->attack = attack; }

    int get_defence() const { return defence; }
    void set_defence(int defence) { this->defence = defence; }
};

class CreatureModifer {
    Game &game;
    Creature &creature;

public:
    CreatureModifer(Game &game, Creature &creature)
        : game { game }, creature { creature } {}
};

class DoubleAttackModifier : public CreatureModifer {
    boost::signals2::connection conn;

public:
    DoubleAttackModifier(Game &game, Creature &creature)
        : CreatureModifer { game, creature } {
        conn = game.queries.connect([&](Query &q) {
            if (q.creature_name == creature.name &&
                q.argument == Query::Argument::attack) {
                q.result *= 2;
            }
        });
    }

    ~DoubleAttackModifier() { conn.disconnect(); }
};

int main(int argc, char *argv[]) {

    Game game;
    Creature goblin { game, "Strong Goblin", 2, 2 };
    std::cout << goblin << std::endl;
    {
        DoubleAttackModifier dam { game, goblin };
        std::cout << goblin << std::endl;
    }
    std::cout << goblin << std::endl;

    return 0;
}

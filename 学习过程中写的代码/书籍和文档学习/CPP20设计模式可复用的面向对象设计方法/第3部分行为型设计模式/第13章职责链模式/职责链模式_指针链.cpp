#include <format>
#include <iostream>
#include <ostream>
#include <string>

struct Creature {
    std::string name;
    int attack, defence;

    friend std::ostream &operator<<(std::ostream &os,
                                    Creature const &creature) {
        return os << std::format("name: {} attack: {} defense: {}",
                                 creature.name, creature.attack,
                                 creature.defence);
    }
};

class CreatureModifer {
    CreatureModifer *next { nullptr };

protected:
    Creature &creature;

public:
    explicit CreatureModifer(Creature &creature) : creature { creature } {}

    // MARK: 写的好呀😘
    void add(CreatureModifer *cm) {
        if (next) {
            next->add(cm);
        } else {
            next = cm;
        }
    }

    virtual void handle() {
        if (next) {
            next->handle();
        }
    }
};

class DoubleAttackModifier : public CreatureModifer {
public:
    explicit DoubleAttackModifier(Creature &creature)
        : CreatureModifer { creature } {}

    void handle() override {
        creature.attack *= 2;
        CreatureModifer::handle();
    }
};

class IncreaseDefenseModifier : public CreatureModifer {
public:
    explicit IncreaseDefenseModifier(Creature &creature)
        : CreatureModifer { creature } {}

    void handle() override {
        if (creature.attack <= 2) {
            creature.defence += 1;
        }
        CreatureModifer::handle();
    }
};

class NoBonusesModifier : public CreatureModifer {
public:
    explicit NoBonusesModifier(Creature &creature)
        : CreatureModifer { creature } {}

    void handle() override {
        // 取消一切奖励
    }
};

int main(int argc, char *argv[]) {

    Creature goblin { "Goblin", 1, 1 };
    CreatureModifer root { goblin };
    DoubleAttackModifier r1 { goblin };
    DoubleAttackModifier r1_2 { goblin };
    IncreaseDefenseModifier r2 { goblin };

    root.add(&r1);
    root.add(&r1_2);
    root.add(&r2);

    root.handle();

    std::cout << goblin << std::endl;

    return 0;
}

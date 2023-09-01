#include <iostream>

// MARK: good 😎😋
template <typename T>
struct Property {
    T value;

    Property(T const initial_value) { *this = initial_value; };

    operator T() { return value; }

    T operator=(T new_value) { return value = new_value; }
};

struct Creature {
    Property<int> strength { 10 };
    Property<int> agility { 5 };
};

int main(int argc, char *argv[]) {

    Creature creature;
    creature.agility = 20;
    auto x { creature.strength };

    return 0;
}

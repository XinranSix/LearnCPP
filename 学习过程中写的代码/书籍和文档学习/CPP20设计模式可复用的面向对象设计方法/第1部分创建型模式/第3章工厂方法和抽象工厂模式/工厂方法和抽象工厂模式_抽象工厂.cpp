#include "fmt/core.h"
#include <iostream>
#include <map>
#include <memory>
#include <string>

struct HotDrink {
    virtual void prepare(int volume) = 0;
};

struct Tea : HotDrink {
    void prepare(int volume) override {
        fmt::print("Take tea bag, boil water, pour {}ml, add some lemon.\n",
                   volume);
    }
};

struct Coffee : HotDrink {
    void prepare(int volume) override {
        fmt::print("Take coffee bag, boil water, pour {}ml, add some lemon.\n",
                   volume);
    }
};

std::unique_ptr<HotDrink> make_drink(std::string type) {
    std::unique_ptr<HotDrink> drink;
    if (type == "tea") {
        drink = std::make_unique<Tea>();
        drink->prepare(200);
    } else {
        drink = std::make_unique<Coffee>();
        drink->prepare(50);
    }
    return drink;
}

class HotDrinkFactory {
public:
    virtual std::unique_ptr<HotDrink> make() const = 0;
};

class CoffeeFactory : public HotDrinkFactory {
public:
    std::unique_ptr<HotDrink> make() const override {
        return std::make_unique<Coffee>();
    }
};

class TeaFactory : public HotDrinkFactory {
public:
    std::unique_ptr<HotDrink> make() const override {
        return std::make_unique<Tea>();
    }
};

class DrinkFacory {
    std::map<std::string, std::unique_ptr<HotDrinkFactory>> hot_factories;

public:
    DrinkFacory() {
        hot_factories["coffee"] = std::make_unique<CoffeeFactory>();
        hot_factories["tea"] = std::make_unique<TeaFactory>();
    }

    std::unique_ptr<HotDrink> make_drink(std::string const &name) {
        auto drink { hot_factories[name]->make() };
        drink->prepare(200);
        return drink;
    }
};

int main(int argc, char *argv[]) { return 0; }

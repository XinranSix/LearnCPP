#include "fmt/core.h"
#include <iostream>
#include <string>
#include <vector>

struct GraphicObject {
    virtual void draw() = 0;
};

struct Circle : GraphicObject {
    void draw() override { fmt::print("Circle\n"); }
};

struct Group : GraphicObject {
    std::string name;

    explicit Group(std::string const &name) : name { name } {}

    void draw() override {
        fmt::print("Group {} contanis:\n", name);
        for (auto &&o : objects) {
            o->draw();
        }
    }

    std::vector<GraphicObject *> objects;
};

int main(int argc, char *argv[]) {

    Group root { "root" };
    Circle c1, c2;
    root.objects.push_back(&c1);

    Group subgroup { "sub" };
    subgroup.objects.push_back(&c2);

    root.objects.push_back(&subgroup);

    root.draw();

    return 0;
}

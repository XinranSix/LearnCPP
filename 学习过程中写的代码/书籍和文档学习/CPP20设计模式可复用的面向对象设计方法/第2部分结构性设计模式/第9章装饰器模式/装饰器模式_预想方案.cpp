#include <iostream>
#include <sstream>
#include <string>

struct Shape {
    virtual std::string str() const = 0;
};

struct Circle : Shape {
    float radius;

    explicit Circle(float const radius) : radius { radius } {}

    void resize(float factor) { radius *= factor; }

    std::string str() const override {
        std::ostringstream oss;
        oss << "A circle of radius " << radius;
        return oss.str();
    }
};

int main(int argc, char *argv[]) { return 0; }

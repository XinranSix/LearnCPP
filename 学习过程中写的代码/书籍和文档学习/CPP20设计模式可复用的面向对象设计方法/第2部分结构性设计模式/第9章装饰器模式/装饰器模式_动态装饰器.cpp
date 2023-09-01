#include "fmt/core.h"
#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>

struct Shape {
    virtual std::string str() const = 0;
};

struct ColoredShape : Shape {

    Shape &shape;
    std::string color;

    ColoredShape(Shape &shape, std::string const &color)
        : shape { shape }, color { color } {}

    std::string str() const override {
        std::ostringstream oss;
        oss << shape.str() << " has the color " << color;
        return oss.str();
    }

    void make_dark() {
        if (constexpr auto dark = "dark"; !color.starts_with(dark)) {
            color.insert(0, dark);
        }
    }
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

struct Square : Shape {
    float side;

    explicit Square(float const side) : side { side } {}

    void resize(float factor) { side *= factor; }

    std::string str() const override {
        std::ostringstream oss;
        oss << "A square with size " << side;
        return oss.str();
    }
};

struct TransparentShape : Shape {
    Shape &shape;
    uint8_t transparency;

    TransparentShape(Shape &shape, uint8_t const transparency)
        : shape { shape }, transparency { transparency } {}

    std::string str() const override {
        std::ostringstream oss;
        oss << shape.str() << " has "
            << static_cast<float>(transparency) / 255.f * 100.f
            << "% transparency";
        return oss.str();
    }
};

int main(int argc, char *argv[]) {

    Circle circle { 0.5f };
    ColoredShape redCircle { circle, "red" };
    std::cout << redCircle.str() << std::endl;

    redCircle.make_dark();
    std::cout << redCircle.str() << std::endl;

    Square square { 3 };
    TransparentShape demiSquare { square, 85 };
    std::cout << demiSquare.str() << std::endl;

    Circle c { 23 };
    ColoredShape cs { c, "green" };
    TransparentShape myCircle { cs, 64 };
    std::cout << myCircle.str() << std::endl;

    return 0;
}

#include "fmt/core.h"
#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>
#include <type_traits>
#include <utility>

struct Shape {
    virtual std::string str() const = 0;
};

template <typename T>
struct ColoredShape : T {
    static_assert(std::is_base_of_v<Shape, T>);
    std::string color;

    template <typename... Args>
    ColoredShape(std::string const &color, Args... args)
        : T { std::forward<Args>(args)... }, color { color } {}

    std::string str() const override {
        std::ostringstream oss;
        // NOTE: C++ 的名称查找要求我们这样写： T::str
        oss << T::str() << " has the color " << color;
        return oss.str();
    }
};

template <typename T>
struct TransparentShape : T {
    static_assert(std::is_base_of_v<Shape, T>);

    uint8_t transparency;

    template <typename... Args>
    TransparentShape(uint8_t const transparency = 0, Args... args)
        : T { std::forward<Args>(args)... }, transparency { transparency } {}

    std::string str() const override {
        std::ostringstream oss;
        oss << T::str() << " has "
            << static_cast<float>(transparency) / 255.f * 100.f
            << "% transparency";
        return oss.str();
    }
};

struct Circle : Shape {
    float radius;

    Circle(float const radius) : radius { radius } {}

    void resize(float factor) { radius *= factor; }

    std::string str() const override {
        std::ostringstream oss;
        oss << "A circle of radius " << radius;
        return oss.str();
    }
};

struct Square : Shape {
    float side;

    Square(float const side = 0) : side { side } {}

    void resize(float factor) { side *= factor; }

    std::string str() const override {
        std::ostringstream oss;
        oss << "A square with size " << side;
        return oss.str();
    }
};

int main(int argc, char *argv[]) {

    ColoredShape<TransparentShape<Square>> square { "blue" };
    square.side = 2;
    square.transparency = 1;
    std::cout << square.str() << std::endl;
    square.resize(3);

    ColoredShape<TransparentShape<Square>> sq { "red", 51, 5 };
    std::cout << sq.str() << std::endl;

    return 0;
}

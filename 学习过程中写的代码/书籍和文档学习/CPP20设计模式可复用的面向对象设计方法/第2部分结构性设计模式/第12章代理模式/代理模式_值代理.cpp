#include <initializer_list>
#include <iostream>
#include <vector>

template <typename T>
struct Value {
    virtual operator T() const = 0;
};

template <typename T>
struct Const : Value<T> {
    T const v;

    Const() : v {} {}

    Const(T v) : v { v } {}

    operator T() const override { return v; }
};

template <typename T>
struct OneOf : Value<T> {
    std::vector<T> values;

    OneOf() : values { { T {} } } {}
    OneOf(std::initializer_list<T> values) : values { values } {}

    operator T() const override { return values[rand() % values.size()]; }
};

void draw_ui(Value<bool> const &use_dark_theme) {
    if (use_dark_theme) {
        std::cout << "Using dark theme\n";
    } else {
        std::cout << "Using normal theme\n";
    }
}

int main(int argc, char *argv[]) {

    Const<int> const life { 42 };

    std::cout << life / 2 << "\n";

    OneOf<int> stuff { 1, 3, 5 };
    std::cout << stuff << "\n";

    OneOf<bool> dark { true, false };
    draw_ui(dark);

    return 0;
}

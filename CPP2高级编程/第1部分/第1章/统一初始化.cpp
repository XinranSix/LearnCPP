#include <iostream>
#include <array>
#include <format>
#include <vector>
#include <compare>
#include <utility>
#include <optional>

struct CircleStruct {
    int x, y;
    double radius;
};

class CircleClass {
public:
    CircleClass(int x, int y, double radius)
        : m_x(x), m_y(y), m_radius(radius) {}

private:
    int m_x, m_y;
    double m_radius;
};

void func(int i) {}

// void func(double i) {}

int main(int arvc, char *argv[]) {

    CircleStruct myCircle1 = {10, 10, 2.5};
    CircleClass myCircle2(10, 10, 2.5);

    CircleStruct myCircle3 = {10, 10, 2.5};
    CircleClass myCircle4 = {10, 10, 2.5};

    CircleStruct myCircle5{10, 10, 2.5};
    CircleClass myCircle6{10, 10, 2.5};

    int a = 3;
    int b(3);
    int c = {3};
    int d{3};

    int e{};

    // int x = 3.14;
    // func(3.14);

    // int x{3.14};
    // func({3.14});

    int *myArray = new int[]{0, 1, 2, 3};

    class MyClass {
    public:
        MyClass() : m_array{0, 1, 2, 3} {}

    private:
        int m_array[4];
    };

    return 0;
}

#include <format>
#include <iostream>
#include <memory>

struct Point {
    Point(int x, int y, int z) : m_x{x}, m_y{y}, m_z{z} {}

    int getX() const { return m_x; }
    int getY() const { return m_y; }
    int getZ() const { return m_z; }

private:
    int m_x, m_y, m_z;
};

void printPoint(Point const &point) {
    std::cout << std::format("x: {}, y: {}, z: {}", point.getX(), point.getY(),
                             point.getZ())
              << std::endl;
}

int main(int argc, char *argv[]) {

    auto pointPtr{std::make_unique<Point>(1, 2, 3)};
    printPoint(*pointPtr);

    return 0;
}

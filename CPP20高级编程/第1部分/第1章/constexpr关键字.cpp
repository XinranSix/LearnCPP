#include <iostream>

// 编译期求值
constexpr int getArraySize() { return 32; }

struct Rect {
public:
    constexpr Rect(size_t width, size_t height)
        : m_width{width}, m_height{height} {}

    constexpr size_t getArea() const { return m_width * m_height; }

private:
    size_t m_width{0}, m_height{0};
};

int main(int arvc, char *argv[]) {

    const int b = 1;

    constexpr int a = getArraySize() + b;

    int myArray[getArraySize() + 1];

    constexpr Rect r{8, 2};
    int myArray1[r.getArea()];

    return 0;
}

#include <iostream>
#include <iterator>
#include <vector>

struct Point {
    int x;
    int y;
};

struct Line {
    Point start;
    Point end;
};

struct VectorObject {
    virtual std::vector<Line>::iterator begin() = 0;
    virtual std::vector<Line>::iterator end() = 0;
};

struct VectorRectangle : VectorObject {
    VectorRectangle(int x, int y, int width, int height) {
        lines.emplace_back(Line { Point { x, y }, Point { x + width, y } });
        lines.emplace_back(
            Line { Point { x + width, y }, Point { x + width, y + height } });
        lines.emplace_back(Line { Point { x, y }, Point { x, y + height } });
        lines.emplace_back(
            Line { Point { x, y + height }, Point { x + width, y + height } });
    }

    std::vector<Line>::iterator begin() override { return std::begin(lines); }
    std::vector<Line>::iterator end() override { return std::end(lines); }

private:
    std::vector<Line> lines;
};

int main(int argc, char *argv[]) { return 0; }

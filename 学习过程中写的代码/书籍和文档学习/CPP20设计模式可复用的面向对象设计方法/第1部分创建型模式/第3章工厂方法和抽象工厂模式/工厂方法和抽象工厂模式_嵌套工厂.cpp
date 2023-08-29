#include <iostream>
#include <memory>

// struct Point2D {
//     int x;
//     int y;
// };

// class Wall {
//     Point2D start, end;
//     int elevation, height;

// public:
//     Wall(Point2D start, Point2D end, int elevation, int height)
//         : start { start }, end { end }, elevation { elevation },
//           height { height } {}

// private:
//     class BasicWallFactory {
//         BasicWallFactory() = default;

//     public:
//         std::shared_ptr<Wall> create(Point2D const start, Point2D const end,
//                                      int const elevation, int const height) {
//             Wall *wall = new Wall { start, end, elevation, height };
//             return std::shared_ptr<Wall> { wall };
//         }
//     };

// public:
//     static BasicWallFactory factory;
// };

int main(int argc, char *argv[]) {

    // auto basic { Wall::factory.create({ 0, 0 }, { 5000, 0 }, 0, 3000) };

    return 0;
}

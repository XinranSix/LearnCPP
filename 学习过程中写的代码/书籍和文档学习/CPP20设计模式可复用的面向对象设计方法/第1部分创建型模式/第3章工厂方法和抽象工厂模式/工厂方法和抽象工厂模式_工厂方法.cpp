#include <format>
#include <iostream>
#include <memory>
#include <ostream>
#include "magic_enum.hpp"

struct Point2D {
    int x;
    int y;
};

struct Wall {
    Point2D start, end;
    int elevation, height;

public:
    Wall(Point2D start, Point2D end, int elevation, int height)
        : start { start }, end { end }, elevation { elevation },
          height { height } {}
};

enum class Material { brick, aerated_concrete, drywall };

class SoildWall : public Wall {
    int width;
    Material material;

protected:
    SoildWall(Point2D start, Point2D end, int elevation, int height, int width,
              Material material)
        : Wall { start, end, elevation, height }, width { width },
          material { material } {}

public:
    friend std::ostream &operator<<(std::ostream &os, SoildWall const &sw) {
        return os << std::format(
                   "start: ({}, {}), end: ({}, {}), elevation: {}, height: "
                   "{}, width: {}, material: {}",
                   sw.start.x, sw.start.y, sw.end.x, sw.end.y, sw.elevation,
                   sw.height, sw.width, magic_enum::enum_name(sw.material));
    }

    /*
        static SoildWall create_main(Point2D start, Point2D end, int elevation,
                                     int height) {
            return SoildWall { start,  end, elevation,
                               height, 375, Material::aerated_concrete };
        }
        */

    static std::shared_ptr<SoildWall> create_main(Point2D start, Point2D end,
                                                  int elevation, int height) {
        if (elevation < 0) {
            return {};
        }
        return std::make_shared<SoildWall>(SoildWall {
            start, end, elevation, height, 375, Material::aerated_concrete });
    }

    static std::unique_ptr<SoildWall>
    create_partition(Point2D start, Point2D end, int evevation, int height) {
        return std::make_unique<SoildWall>(
            SoildWall { start, end, evevation, height, 120, Material::brick });
    }
};

int main(int argc, char *argv[]) {

    auto const main_wall { SoildWall::create_main({ 0, 0 }, { 0, 3000 }, 2700,
                                                  3000) };

    std::cout << *main_wall << std::endl;

    auto const also_main_wall { SoildWall::create_main({ 0, 0 }, { 10000, 0 },
                                                       -2000, 3000) };
    if (!also_main_wall) {
        std::cout << "Main wall not created\n";
    }

    return 0;
}

#include <format>
#include <iostream>
#include <memory>
#include <ostream>
#include <vector>
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

    friend class WallFactory;

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
    create_partition(Point2D start, Point2D end, int elevation, int height) {
        return std::make_unique<SoildWall>(
            SoildWall { start, end, elevation, height, 120, Material::brick });
    }
};

class WallFactory {
    static std::vector<std::weak_ptr<Wall>> walls;

public:
    static std::shared_ptr<SoildWall> create_main(Point2D start, Point2D end,
                                                  int elevation, int height) {
        if (elevation < 0) {
            return {};
        }
        return std::make_shared<SoildWall>(SoildWall {
            start, end, elevation, height, 375, Material::aerated_concrete });
    }

    static std::shared_ptr<SoildWall>
    create_partition(Point2D start, Point2D end, int elevation, int height) {
        auto const this_wall { new SoildWall { start, end, elevation, height,
                                               120, Material::brick } };

        // for (auto const wall : walls) {
        // 一顿判断
        // }
        // std::shared_ptr<SoildWall> ptr { this_wall };
        // std::weak_ptr<Wall> pq { ptr };
        // walls.push_back(pq);
        // return ptr;

        return {};
    }
};

int main(int argc, char *argv[]) {

    auto const partiton { WallFactory::create_partition(
        { 2000, 0 }, { 2000, 4000 }, 1, 2700) };

    std::cout << *partiton << std::endl;

    return 0;
}

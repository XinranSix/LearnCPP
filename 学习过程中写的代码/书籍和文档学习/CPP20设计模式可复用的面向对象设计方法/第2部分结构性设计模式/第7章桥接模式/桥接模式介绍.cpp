#include "fmt/core.h"
#include <iostream>

struct Renderer {
    virtual void render_circle(float x, float y, float radius) = 0;
};

struct VectorRenderer : Renderer {
    void render_circle(float x, float y, float radius) override {
        fmt::print("Rasterizing circle of radius {}\n", radius);
    }
};

struct RasterRenderer : Renderer {
    void render_circle(float x, float y, float radius) override {
        fmt::print("Drawing a vector circle of radius {}\n", radius);
    }
};

struct Shape {
protected:
    Renderer &renderer;
    Shape(Renderer &renderer) : renderer { renderer } {}

public:
    virtual void draw() = 0;
    virtual void resize(float factor) = 0;
};

struct Cirle : Shape {
    float x, y, radius;

    Cirle(Renderer &renderer, float x, float y, float radius)
        : Shape { renderer }, x { x }, y { y }, radius { radius } {}

    void draw() override { renderer.render_circle(x, y, radius); }

    void resize(float factor) override { radius *= factor; }
};

int main(int argc, char *argv[]) {

    RasterRenderer rr;
    Cirle raster_circle { rr, 5, 5, 5 };
    raster_circle.draw();
    raster_circle.resize(2);
    raster_circle.draw();

    return 0;
}

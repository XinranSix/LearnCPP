#include <iostream>
#include <string>
#include <utility>

struct Image {
    virtual void draw() = 0;
};

struct Bitmap : Image {
    Bitmap(std::string filename) : filename { std::move(filename) } {
        std::cout << "Loading image from " << this->filename << std::endl;
    }

    void draw() override {
        std::cout << "Drawing image " << filename << std::endl;
    }

private:
    std::string filename;
};

struct LazyBitmap : Image {
    LazyBitmap(std::string const &filename)
        : filename { std::move(filename) } {}

    ~LazyBitmap() { delete bmp; }

    void draw() override {
        if (!bmp) {
            bmp = new Bitmap { filename };
        }
        bmp->draw();
    }

private:
    Bitmap *bmp { nullptr };
    std::string filename;
};

void draw_image(Image &img) {
    std::cout << "About to draw the image\n";
    img.draw();
    std::cout << "Done drawing the image\n";
}

int main(int argc, char *argv[]) {

    Bitmap img { "pokemen.png" };

    LazyBitmap img1 { "pokemen.png" };

    draw_image(img1);

    return 0;
}

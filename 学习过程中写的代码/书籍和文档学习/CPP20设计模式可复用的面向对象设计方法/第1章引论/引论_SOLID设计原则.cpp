#include "fmt/core.h"
#include <boost/di.hpp>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <gtest/gtest.h>
#include <iostream>
#include <memory>
#include <ostream>
#include <string>
#include <vector>
#include <boost/lexical_cast.hpp>

/*
SOLID:
Single Responsibility Principle, SRP
Open-Closed Principle, OCP
Liskov Substitution Principle, LSP
Interface Segregation Principle, ISP
Dependency Inversion Principle, DIP
*/

struct Journal {
    std::string title;
    std::vector<std::string> entries;

    explicit Journal(std::string const &title) : title { title } {}

    void add(std::string const &entry) {
        static int count = 1;
        entries.push_back(boost::lexical_cast<std::string>(count++) + ": " +
                          entry);
    }

    // void save(std::string const &filename) {
    //     std::ofstream ofs { filename };
    //     for (auto &s : entries) {
    //         ofs << s << std::endl;
    //     }
    // }
};

struct PersistenceManager {

    static void save(Journal const &j, std::string const &filename) {
        std::ofstream ofs { filename };
        for (auto &s : j.entries) {
            ofs << s << std::endl;
        }
    }
};

TEST(SOLID设计原则, 单一职责原则) {
    Journal j { "Dear Diary" };
    j.add("I cried today");
    j.add("I ate a bug");
}

enum class Color { Red, Green, Blue };
enum class Size { Small, Medium, Large };

struct Product {
    std::string name;
    Color color;
    Size size;
};

// struct ProductFilter {
//     using Items = std::vector<Product *>;

// Items by_color(Items items, Color color) {
//     Items result;
//     for (auto &i : items) {
//         if (i->color == color) {
//             result.push_back(i);
//         }
//     }
//     return result;
// }

// Items by_size(Items items, Size size) {
//     Items result;
//     for (auto &i : items) {
//         if (i->size == size) {
//             result.push_back(i);
//         }
//     }
//     return result;
// }
// };

template <typename T>
struct AndSpecification;

template <typename T>
struct Specifcation {
    virtual bool is_satisfied(T *item) = 0;

    // AndSpecification<T> operator&&(Specifcation &other) {
    //     return AndSpecification<T> { *this, other };
    // }
};

template <typename T>
AndSpecification<T> operator&&(Specifcation<T> &first,
                               Specifcation<T> &second) {
    return AndSpecification<T> { first, second };
}

template <typename T>
struct Filter {
    virtual std::vector<T *> filter(std::vector<T *> items,
                                    Specifcation<T> &spec) const = 0;
};

struct BetterFilter : Filter<Product> {
    std::vector<Product *> filter(std::vector<Product *> items,
                                  Specifcation<Product> &spec) const override {
        std::vector<Product *> result;
        for (auto &p : items) {
            if (spec.is_satisfied(p)) {
                result.push_back(p);
            }
        }
        return result;
    }
};

struct ColorSpecification : Specifcation<Product> {
    Color color;

    explicit ColorSpecification(Color const color) : color { color } {}

    bool is_satisfied(Product *item) override { return item->color == color; }
};

struct SizeSpecification : Specifcation<Product> {
    Size size;

    explicit SizeSpecification(Size const size) : size { size } {}

    bool is_satisfied(Product *item) override { return item->size == size; }
};

template <typename T>
struct AndSpecification : Specifcation<T> {
    Specifcation<T> &first;
    Specifcation<T> &second;

    AndSpecification(Specifcation<T> &first, Specifcation<T> &second)
        : first { first }, second { second } {}

    bool is_satisfied(T *item) override {
        return first.is_satisfied(item) && second.is_satisfied(item);
    }
};

TEST(SOLID设计原则, 开闭原则) {
    Product apple { "Apple", Color::Green, Size::Small };
    Product tree { "Tree", Color::Green, Size::Large };
    Product house { "House", Color::Blue, Size::Large };

    std::vector<Product *> all { &apple, &tree, &house };

    BetterFilter bf;
    ColorSpecification green { Color::Green };

    auto green_things = bf.filter(all, green);
    for (auto &x : green_things) {
        std::cout << x->name << " is green" << std::endl;
    }

    /* ---------------------------------------------------------------------- */
    {
        SizeSpecification large { Size::Large };
        ColorSpecification green { Color::Green };
        AndSpecification<Product> green_and_large { large, green };
        auto big_green_things { bf.filter(all, green_and_large) };
        for (auto &x : big_green_things) {
            std::cout << x->name << " is large and green.\n";
        }
    }

    /* ---------------------------------------------------------------------- */
    {
        SizeSpecification large { Size::Large };
        ColorSpecification green { Color::Green };
        AndSpecification<Product> green_and_large { large && green };
        auto big_green_things { bf.filter(all, green_and_large) };
        for (auto &x : big_green_things) {
            std::cout << x->name << " is large and green.\n";
        }
    }
}

class Rectangle {
public:
    Rectangle(int const width, int const height)
        : width { width }, height { height } {};

    int get_width() const { return width; }

    virtual void set_width(int const width) { this->width = width; }

    int get_height() const { return height; }

    virtual void set_height(int const height) { this->height = height; }

    int area() const { return width * height; }

    bool is_square() const { return width == height; }

protected:
    int width {};
    int height {};
};

class Square : public Rectangle {
public:
    Square(int size) : Rectangle { size, size } {}

    void set_width(int const width) override { this->width = width; }

    void set_height(int const height) override { this->height = height; }
};

void process(Rectangle &r) {
    int w = r.get_width();
    r.set_height(10);
    fmt::print("expected area = {}, got {}\n", w * 10, r.area());
}

struct RectangleFactory {
    static Rectangle create_rectangle(int w, int h);
    static Rectangle create_square(int size);
};

TEST(SOLID设计原则, 里氏替换原则) {
    Square s { 5 };
    process(s);
}

struct Document {};

struct IPrinter {
    virtual void print(std::vector<Document *> docs) = 0;
};

struct IScanner {
    virtual void scan(std::vector<Document *> docs) = 0;
};

struct Printer : IPrinter {
    void print(std::vector<Document *> docs) override {}
};

struct Scanner : IScanner {
    void scan(std::vector<Document *> docs) override {}
};

struct IMachine : IPrinter, IScanner {};

struct Machine : IMachine {
    IPrinter &printer;
    IScanner &scanner;

    Machine(IPrinter &printer, IScanner &scanner)
        : printer { printer }, scanner { scanner } {}

    void print(std::vector<Document *> docs) override { printer.print(docs); }

    void scan(std::vector<Document *> docs) override { scanner.scan(docs); }
};

TEST(SOLID设计原则, 接口隔离原则) {}

struct ILogger {
    virtual ~ILogger() {}
    virtual void Log(const std::string &s) = 0;
};

struct ConsoleLogger : ILogger {
    ConsoleLogger() {}

    void Log(const std::string &s) override {
        std::cout << "LOG: " << s.c_str() << std::endl;
    }
};

struct Engine {
    float volume = 5;      // 音量5
    int horse_power = 400; // 马力400

    Engine(float volume_, int horse_power_)
        : volume { volume_ }, horse_power { horse_power_ } {}

    friend std::ostream &operator<<(std::ostream &os, const Engine &engine) {
        return os << "volume: " << engine.volume
                  << " horse_power: " << engine.horse_power;
    }

    // friend std::ostream &operator<<(std::ostream &os,
    //                                 const std::shared_ptr<Engine> &engine) {
    //     return os << "volume: " << engine->volume
    //               << " horse_power: " << engine->horse_power;
    // }
};

struct Car {
    std::unique_ptr<Engine> engine;
    std::shared_ptr<ILogger> logger;

    Car(std::unique_ptr<Engine> engine, const std::shared_ptr<ILogger> &logger)
        : engine { std::move(engine) }, logger { logger } {

        logger->Log("making a car");
    }

    friend std::ostream &operator<<(std::ostream &os, const Car &car) {
        return os << "Car with engine: " << *car.engine;
    }

    // friend std::ostream &operator<<(std::ostream &os,
    //                                 const std::shared_ptr<Car> &car) {
    //     return os << "Car with engine: " << *car->engine;
    // }
};

TEST(SOLID设计原则, 依赖倒转原则) {
    auto injector { boost::di::make_injector(
        boost::di::bind<ILogger>().to<ConsoleLogger>()) };

    auto car { injector.create<std::shared_ptr<Car>>() };

    std::cout << *car << std::endl;
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

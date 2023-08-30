#include <algorithm>
#include <memory>
#include <utility>
#include <vector>
#include <iostream>

enum class Color { Red, Green, Blue };
enum class Size { Small, Medium, Large };

struct Product {
    std::string name;
    Color color;
    Size size;
};

template <typename T>
struct AndSpecification;

template <typename T>
struct Specifcation {
    virtual bool is_satisfied(T *item) = 0;

    AndSpecification<T> operator&&(Specifcation &other) {
        return AndSpecification<T> { *this, other };
    }
};

template <typename T>
struct CompositeSpecification : Specifcation<T> {
protected:
    std::vector<std::unique_ptr<Specifcation<T>>> specs;

    template <typename... Specs>
    CompositeSpecification(Specs... specs) {
        this->specs.reserve(sizeof...(Specs));
        (this->specs.push_back(std::make_unique<Specs>(std::move(specs))), ...);
    }
};

template <typename T>
struct AndSpecification : CompositeSpecification<T> {
    template <typename... Specs>
    AndSpecification(Specs... specs) : CompositeSpecification<T> { specs... } {}

    bool is_satisfied(T *item) const override {
        return std::all_of(
            std::begin(this->specs), std::end(this->specs),
            [=](auto const &s) { return s->is_satisfied(item); });
    }
};

int main(int argc, char *argv[]) {

    // auto spec{AndSpecification<Product>{greem, large, cheap}};

    return 0;
}

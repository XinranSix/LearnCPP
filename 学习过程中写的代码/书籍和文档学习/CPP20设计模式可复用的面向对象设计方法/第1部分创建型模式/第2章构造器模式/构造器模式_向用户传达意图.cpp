#include "fmt/core.h"
#include <cstddef>
#include <format>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

struct HtmlBuilder;

struct HtmlElement {

    friend struct HtmlBuilder;

    std::string name;
    std::string text;
    std::vector<HtmlElement> elements;

    size_t const index_size = 2;

    static std::unique_ptr<HtmlBuilder> create(std::string const &root_name) {
        return std::make_unique<HtmlBuilder>(root_name);
    }

    std::string str(int index = 0) const {
        std::ostringstream oss;
        oss << std::format("<{}>", name);
        oss << std::format("{}", text);
        for (auto const &element : elements) {
            oss << element.str();
        }
        oss << std::format("</{}>", name);
        return oss.str();
    }

protected:
    HtmlElement() {}
    HtmlElement(std::string const &name, std::string const &text)
        : name { name }, text { text } {}
};

struct HtmlBuilder {

    operator HtmlElement() const { return root; }

    HtmlElement build() const { return root; }

    HtmlElement root;

    HtmlBuilder(std::string root_name) { root.name = root_name; }

    HtmlBuilder &add_child(std::string child_name, std::string child_text) {
        root.elements.push_back({ child_name, child_text });
        return *this;
    }

    std::string str() { return root.str(); }
};

int main(int argc, char *argv[]) {

    auto builder = HtmlElement::create("ul");
    builder->add_child("li", "hello").add_child("li", "world");
    fmt::print("{}\n", builder->str());

    /* ---------------------------------------------------------------------- */
    HtmlElement e { HtmlElement::create("ul")
                        ->add_child("li", "hello")
                        .add_child("li", "world") };
    fmt::print("{}\n", e.str());

    return 0;
}

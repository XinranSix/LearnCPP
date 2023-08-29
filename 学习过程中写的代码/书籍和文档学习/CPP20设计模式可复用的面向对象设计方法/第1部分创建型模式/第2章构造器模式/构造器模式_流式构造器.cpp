#include "fmt/core.h"
#include <format>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct HtmlElement {
    std::string name;
    std::string text;
    std::vector<HtmlElement> elements;

    HtmlElement() {}
    HtmlElement(std::string const &name, std::string const &text)
        : name { name }, text { text } {}

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
};

struct HtmlBuilder {

    HtmlElement root;

    HtmlBuilder(std::string root_name) { root.name = root_name; }

    HtmlBuilder &add_child(std::string child_name, std::string child_text) {
        root.elements.emplace_back(child_name, child_text);
        return *this;
    }

    std::string str() { return root.str(); }
};

int main(int argc, char *argv[]) {

    HtmlBuilder builder { "ul" };
    builder.add_child("li", "hello").add_child("li", "world");
    fmt::print("{}\n", builder.str());

    return 0;
}

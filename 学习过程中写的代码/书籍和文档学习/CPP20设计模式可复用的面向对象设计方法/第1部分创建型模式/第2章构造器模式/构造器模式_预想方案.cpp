#include "fmt/core.h"
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
        //
        return elements[index].text;
    }
};

int main(int argc, char *argv[]) {
    /*
        std::string words[] { "hello", "world" };
        std::ostringstream oss;

        oss << "<ul>\n";
        for (auto &w : words) {
            oss << fmt::format("    <li>{}</li>\n", w);
        }
        oss << "</ul>";
        fmt::print("{}\n", oss.str());
        */

    /* ---------------------------------------------------------------------- */
    std::string words[] { "hello", "world" };

    HtmlElement list { "ul", "" };

    for (auto w : words) {
        list.elements.emplace_back("li", w);
    }

    fmt::print("{}", list.str());

    return 0;
}

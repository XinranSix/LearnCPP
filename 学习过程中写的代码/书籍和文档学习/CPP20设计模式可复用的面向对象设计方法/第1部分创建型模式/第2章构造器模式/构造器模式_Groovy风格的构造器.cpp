#include <format>
#include <initializer_list>
#include <iostream>
#include <ostream>
#include <string>
#include <utility>
#include <vector>

// MARK: 此文档创建了 DSL
struct Tag {
    std::string name;
    std::string text;

    std::vector<Tag> children;
    std::vector<std::pair<std::string, std::string>> attributes;

    friend std::ostream &operator<<(std::ostream &os, Tag const &tag) {

        os << "<" << tag.name;
        for (auto const &[k, v] : tag.attributes) {
            os << " " << k << "="
               << "\"" << v << "\"";
        }
        os << ">" << tag.text;
        for (auto const &child : tag.children) {
            os << child;
        }
        os << std::format("</{}>", tag.name);
        return os;
    }

protected:
    Tag(std::string const &name, std::string const &text)
        : name { name }, text { text } {}

    Tag(std::string const &name, std::vector<Tag> const &children)
        : name { name }, children { children } {}
};

struct P : Tag {
    explicit P(std::string const &text) : Tag { "p", text } {}

    P(std::initializer_list<Tag> children) : Tag { "p", children } {}
};

struct IMG : Tag {
    explicit IMG(std::string const &url) : Tag { "img", "" } {
        attributes.emplace_back("src", url);
    }
};

int main(int argc, char *argv[]) {

    std::cout << P { IMG { "http:://pokemon.com/pikachu.png" } } << std::endl;

    return 0;
}

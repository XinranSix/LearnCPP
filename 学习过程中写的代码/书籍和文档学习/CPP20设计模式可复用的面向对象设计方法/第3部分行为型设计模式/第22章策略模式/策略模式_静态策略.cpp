#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

enum class OutputFormat { markdown, html };

struct ListStrategy {
    virtual void start(std::ostringstream &oss) {};
    virtual void add_list_item(std::ostringstream &oss,
                               std::string const &item) {}
    virtual void end(std::ostringstream &oss) {}
};

struct TextProcessor {

    void append_list(std::vector<std::string> items) {
        list_strategy->start(oss);
        for (auto &item : items) {
            list_strategy->add_list_item(oss, item);
        }
        list_strategy->end(oss);
    }

private:
    std::ostringstream oss;
    std::unique_ptr<ListStrategy> list_strategy;
};

struct HtmlListStrategy : ListStrategy {
    void start(std::ostringstream &oss) override { oss << "<ul>\n"; }

    void end(std::ostringstream &oss) override { oss << "</ul>\n"; }

    void add_list_item(std::ostringstream &oss,
                       std::string const &item) override {
        oss << "    <li>" << item << "</li>\n";
    }
};

struct MarkdownListStrategy : ListStrategy {
    void add_list_item(std::ostringstream &oss,
                       std::string const &item) override {
        oss << "*" << item;
    }
};

int main(int argc, char *argv[]) {

    // TextProcessor tp { OutputFormat::markdown };
    // tp.append_list({});

    return 0;
}

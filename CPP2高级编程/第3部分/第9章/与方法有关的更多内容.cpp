#include <iostream>
#include <gtest/gtest.h>
#include "professional_cpp/spreadsheet.hpp"
#include "professional_cpp/spreadsheetCell.hpp"

TEST(与方法有关的更多内容, const函数和非const函数重载) {
    Spreadsheet sheet1 { 5, 6 };
    SpreadsheetCell &cell1 { sheet1.getCellAt(1, 1) };

    const Spreadsheet sheet2 { 5, 6 };
    const SpreadsheetCell &cell2 { sheet2.getCellAt(1, 1) };
}

class TextHolder {
public:
    TextHolder(std::string text) : m_text { std::move(text) } {
    }

    const std::string &getText() const & {
        return m_text;
    };

    std::string &&getText() && {
        return std::move(m_text);
    };

private:
    std::string m_text;
};

TEST(与方法有关的更多内容, 引用限定方法) {
    TextHolder textHolder { "Hello World!" };

    std::cout << textHolder.getText() << std::endl;
    std::cout << TextHolder { "Hello World!" }.getText() << std::endl;
    std::cout << std::move(textHolder).getText() << std::endl;
}



int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

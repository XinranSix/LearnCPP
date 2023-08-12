#ifndef STRING_SPREADSHEET_CELL1_HPP
#define STRING_SPREADSHEET_CELL1_HPP

#include "professional_cpp/spreadsheetCell1.hpp"
#include <optional>
#include <string_view>
#include <iostream>

class StringSpreadsheetCell : public SpreadsheetCell {
public:
    void set(std::string_view value) override {
        std::cout << "test" << std::endl;
        // m_value = value;
    }
    std::string getString() const override {
        return m_value.value_or("");
    }

private:
    std::optional<std::string> m_value;
};

#endif

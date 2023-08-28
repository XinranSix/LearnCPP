#ifndef SPREADSHEET_CELL1_HPP
#define SPREADSHEET_CELL1_HPP

#include <string_view>

class SpreadsheetCell {
public:
    virtual ~SpreadsheetCell() = default;
    virtual void set(std::string_view value) = 0;
    virtual std::string getString() const = 0;
};

#endif

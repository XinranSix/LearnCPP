#ifndef SPREADSHEET_CELL_HPP
#define SPREADSHEET_CELL_HPP

#include <string>
#include <string_view>
#include <charconv>
#include <iostream>

class SpreadsheetCell {
public:
    SpreadsheetCell() = default;
    explicit SpreadsheetCell(double initialValue);
    explicit SpreadsheetCell(std::string_view initialValue);
    SpreadsheetCell(SpreadsheetCell const &src);
    ~SpreadsheetCell();

public:
    SpreadsheetCell &operator=(SpreadsheetCell const &rhs);
    SpreadsheetCell operator+(SpreadsheetCell const &cell) const;

public:
    void setValue(double value);
    double getValue() const;

    void setString(std::string_view value);
    std::string getString() const;

private:
    static std::string doubleToString(double value);
    static double stringToDouble(std::string_view value);
    double m_value {};
    mutable size_t m_numAccesses { 0 };
};

SpreadsheetCell::SpreadsheetCell(double initialValue)
    : m_value { initialValue } {
}

SpreadsheetCell::SpreadsheetCell(std::string_view initialValue) {
    setString(initialValue);
}

SpreadsheetCell::~SpreadsheetCell() {
    // std::cout << "解构子" << std::endl;
}

void SpreadsheetCell::setValue(double value) {
    m_value = value;
}

inline double SpreadsheetCell::getValue() const {
    ++m_numAccesses;
    return m_value;
}

SpreadsheetCell::SpreadsheetCell(SpreadsheetCell const &src)
    : m_value { src.m_value } {
}

SpreadsheetCell &SpreadsheetCell::operator=(SpreadsheetCell const &rhs) {
    if (this == &rhs) {
        return *this;
    }
    m_value = rhs.m_value;
    return *this;
}

SpreadsheetCell SpreadsheetCell::operator+(SpreadsheetCell const &cell) const {
    return SpreadsheetCell { getValue() + cell.getValue() };
}

inline void SpreadsheetCell::setString(std::string_view value) {
    m_value = stringToDouble(value);
}

std::string SpreadsheetCell::getString() const {
    ++m_numAccesses;
    return doubleToString(m_value);
}

std::string SpreadsheetCell::doubleToString(double value) {
    return std::to_string(value);
}

double SpreadsheetCell::stringToDouble(std::string_view value) {
    double number { 0 };
    std::from_chars(value.data(), value.data() + value.size(), number);
    return number;
}

#endif
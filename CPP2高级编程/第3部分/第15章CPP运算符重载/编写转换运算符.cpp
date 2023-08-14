#include <cstddef>
#include <iostream>
#include <gtest/gtest.h>
#include <memory>
#include <ostream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <charconv>
#include <iostream>
#include <utility>

class SpreadsheetCell {
public:
    SpreadsheetCell() = default;
    SpreadsheetCell(double initialValue);
    explicit SpreadsheetCell(std::string_view initialValue);
    SpreadsheetCell(SpreadsheetCell const &src);
    ~SpreadsheetCell();

public:
    SpreadsheetCell &operator=(SpreadsheetCell const &rhs);
    SpreadsheetCell operator+(SpreadsheetCell const &cell) const;
    SpreadsheetCell operator-() const;

    SpreadsheetCell &operator++();
    SpreadsheetCell operator++(int);
    SpreadsheetCell &operator--();
    SpreadsheetCell operator--(int);

public:
    void setValue(double value);
    double getValue() const;

    void setString(std::string_view value);
    std::string getString() const;

    friend std::ostream &operator<<(std::ostream &ostr,
                                    SpreadsheetCell const &cell);
    friend std::istream &operator>>(std::istream &istr, SpreadsheetCell &cell);

public:
    explicit operator double() const;
    operator std::string() const;

private:
    static std::string doubleToString(double value);
    static double stringToDouble(std::string_view value);
    double m_value {};
    mutable size_t m_numAccesses { 0 };
};

SpreadsheetCell::SpreadsheetCell(double initialValue)
    : m_value { initialValue } {}

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
    : m_value { src.m_value } {}

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

SpreadsheetCell SpreadsheetCell::operator-() const {
    return SpreadsheetCell { -getValue() };
}

SpreadsheetCell &SpreadsheetCell::operator++() {
    setValue(getValue() + 1);
    return *this;
}

SpreadsheetCell SpreadsheetCell::operator++(int) {
    auto oldCell { *this };
    ++(*this);
    return oldCell;
}

SpreadsheetCell &SpreadsheetCell::operator--() {
    setValue(getValue() - 1);
    return *this;
}

SpreadsheetCell SpreadsheetCell::operator--(int) {
    auto oldCell { *this };
    --(*this);
    return oldCell;
}

std::ostream &operator<<(std::ostream &ostr, SpreadsheetCell const &cell) {
    ostr << cell.getValue();
    return ostr;
}

std::istream &operator>>(std::istream &istr, SpreadsheetCell &cell) {
    double value {};
    istr >> value;
    cell.setValue(value);
    return istr;
}

/* -------------------------------------------------------------------------- */
SpreadsheetCell::operator double() const {
    return getValue();
}

SpreadsheetCell::operator std::string() const {
    return doubleToString(getValue());
}

TEST(编写转换运算符, C) {
    SpreadsheetCell cell { 1.23 };
    double d1 { cell };
    std::cout << d1 << std::endl;

    std::string str = cell;
    std::string str2 { static_cast<std::string>(cell) };
    std::cout << str << '\n' << str2 << std::endl;
}

TEST(编写转换运算符, 使用显示转换运算符解决多义性问题) {
    SpreadsheetCell cell { 6.6 };
    double d2 { cell + 2.3 };
}

TEST(编写转换运算符, 用于布尔表达式的转换) {}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

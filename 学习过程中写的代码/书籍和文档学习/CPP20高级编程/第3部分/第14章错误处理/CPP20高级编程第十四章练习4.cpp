#include <exception>
#include <iostream>
#include <string>
#include <string_view>
#include <charconv>
#include <cstddef>
#include <stdexcept>
#include <utility>
#include <format>
#include <iostream>

class InvalidCoordinate : public std::exception {
public:
    InvalidCoordinate(size_t x, size_t y, size_t maxX, size_t maxY)
        : m_x { x }, m_y { y }, m_maxX { maxX }, m_maxY { maxY } {
        m_message = std::format(
            "Corrdinate ({}, {}) is not within the range ({}, {}) - ({}, {}).",
            m_x, m_y, 0, 0, m_maxX, m_maxY);
    }

    const char *what() const noexcept override {
        return m_message.c_str();
    }

private:
    size_t m_x { 0 }, m_y { 0 };

    size_t m_maxX { 0 }, m_maxY { 0 };

    std::string m_message;
};

/* -------------------------------------------------------------------------- */

class SpreadsheetCell {
public:
    SpreadsheetCell() = default;
    SpreadsheetCell(double initialValue);
    SpreadsheetCell(std::string_view initialValue);

    void setValue(double value);
    double getValue() const;

    void setString(std::string_view value);
    std::string getString() const;

private:
    std::string doubleToString(double value) const;
    double stringToDouble(std::string_view value) const;

    double m_value { 0 };
};

SpreadsheetCell::SpreadsheetCell(double initialValue)
    : m_value { initialValue } {}

SpreadsheetCell::SpreadsheetCell(std::string_view initialValue)
    : m_value { stringToDouble(initialValue) } {}

void SpreadsheetCell::setValue(double value) {
    m_value = value;
}

double SpreadsheetCell::getValue() const {
    return m_value;
}

void SpreadsheetCell::setString(std::string_view value) {
    m_value = stringToDouble(value);
}

std::string SpreadsheetCell::getString() const {
    return doubleToString(m_value);
}

std::string SpreadsheetCell::doubleToString(double value) const {
    return std::to_string(value);
}

double SpreadsheetCell::stringToDouble(std::string_view value) const {
    double number { 0 };
    std::from_chars(value.data(), value.data() + value.size(), number);
    return number;
}

/* -------------------------------------------------------------------------- */

class Spreadsheet {
public:
    Spreadsheet(size_t width, size_t height);
    Spreadsheet(const Spreadsheet &src);
    Spreadsheet(Spreadsheet &&src) noexcept; // Move constructor
    ~Spreadsheet();

    Spreadsheet &operator=(const Spreadsheet &rhs);
    Spreadsheet &operator=(Spreadsheet &&rhs) noexcept; // Move assignment

    void setCellAt(size_t x, size_t y, const SpreadsheetCell &cell);
    SpreadsheetCell &getCellAt(size_t x, size_t y);

    void swap(Spreadsheet &other) noexcept;

private:
    void verifyCoordinate(size_t x, size_t y) const;

    size_t m_width { 0 };
    size_t m_height { 0 };
    SpreadsheetCell **m_cells { nullptr };
};

void swap(Spreadsheet &first, Spreadsheet &second) noexcept;

Spreadsheet::Spreadsheet(size_t width, size_t height)
    : m_width { width }, m_height { height } {
    std::cout << "Normal constructor" << std::endl;

    m_cells = new SpreadsheetCell *[m_width];
    for (size_t i { 0 }; i < m_width; i++) {
        m_cells[i] = new SpreadsheetCell[m_height];
    }
}

Spreadsheet::~Spreadsheet() {
    for (size_t i { 0 }; i < m_width; i++) {
        delete[] m_cells[i];
    }
    delete[] m_cells;
    m_cells = nullptr;
}

Spreadsheet::Spreadsheet(const Spreadsheet &src)
    : Spreadsheet { src.m_width, src.m_height } {
    std::cout << "Copy constructor" << std::endl;

    // The ctor-initializer of this constructor delegates first to the
    // non-copy constructor to allocate the proper amount of memory.

    // The next step is to copy the data.
    for (size_t i { 0 }; i < m_width; i++) {
        for (size_t j { 0 }; j < m_height; j++) {
            m_cells[i][j] = src.m_cells[i][j];
        }
    }
}

void Spreadsheet::verifyCoordinate(size_t x, size_t y) const {
    if (x >= m_width) {
        throw std::out_of_range { std::format("{} must be less than {}.", x,
                                              m_width) };
    }
    if (y >= m_height) {
        throw std::out_of_range { std::format("{} must be less than {}.", y,
                                              m_height) };
    }
}

void Spreadsheet::setCellAt(size_t x, size_t y, const SpreadsheetCell &cell) {
    verifyCoordinate(x, y);
    m_cells[x][y] = cell;
}

SpreadsheetCell &Spreadsheet::getCellAt(size_t x, size_t y) {
    verifyCoordinate(x, y);
    return m_cells[x][y];
}

void Spreadsheet::swap(Spreadsheet &other) noexcept {
    std::swap(m_width, other.m_width);
    std::swap(m_height, other.m_height);
    std::swap(m_cells, other.m_cells);
}

void swap(Spreadsheet &first, Spreadsheet &second) noexcept {
    first.swap(second);
}

Spreadsheet &Spreadsheet::operator=(const Spreadsheet &rhs) {
    std::cout << "Copy assignment operator" << std::endl;

    // Copy-and-swap idiom
    Spreadsheet temp { rhs }; // Do all the work in a temporary instance
    swap(temp); // Commit the work with only non-throwing operations
    return *this;
}

// Move constructor
Spreadsheet::Spreadsheet(Spreadsheet &&src) noexcept {
    std::cout << "Move constructor" << std::endl;

    ::swap(*this, src);
}

// Move assignment operator
Spreadsheet &Spreadsheet::operator=(Spreadsheet &&rhs) noexcept {
    std::cout << "Move assignment operator" << std::endl;

    ::swap(*this, rhs);
    return *this;
}

int main(int argc, char *argv[]) {
    return 0;
}

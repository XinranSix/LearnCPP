#ifndef SPREADSHEET_HPP
#define SPREADSHEET_HPP

#include <cstddef>
#include <format>
#include <iterator>
#include <stdexcept>
#include <utility>
#include <xstring>
#include "professional_cpp/spreadsheetCell.hpp"
#include "spreadsheetCell.hpp"

class Spreadsheet {
public:
    Spreadsheet(size_t width, size_t height);
    Spreadsheet(Spreadsheet const &src);
    Spreadsheet(Spreadsheet &&src) noexcept;
    ~Spreadsheet();
    Spreadsheet &operator=(Spreadsheet const &rhs);
    Spreadsheet &operator=(Spreadsheet &&rhs) noexcept;
    void setCellAt(size_t x, size_t y, SpreadsheetCell const &cell);
    SpreadsheetCell &getCellAt(size_t x, size_t y);
    const SpreadsheetCell &getCellAt(size_t x, size_t y) const;
    void swap(Spreadsheet &other) noexcept;
    size_t getId() const;

public:
    static const size_t MaxHeight { 100 };
    static const size_t MaxWidth { 100 };

private:
    // void cleanup() noexcept;
    // void moveFrom(Spreadsheet &src) noexcept;
    void verifyCoordinate(size_t x, size_t y) const;
    size_t m_width { 0 };
    size_t m_height { 0 };
    SpreadsheetCell **m_cells { nullptr };
    static inline size_t ms_counter { 0 };
    const size_t m_id { 0 };
};

// size_t Spreadsheet::ms_counter { 0 };

void swap(Spreadsheet &first, Spreadsheet &second) noexcept;

size_t Spreadsheet::getId() const {
    return m_id;
}

SpreadsheetCell &Spreadsheet::getCellAt(size_t x, size_t y) {
    verifyCoordinate(x, y);
    return m_cells[x][y];
}

const SpreadsheetCell &Spreadsheet::getCellAt(size_t x, size_t y) const {
    return const_cast<SpreadsheetCell &>(std::as_const(*this).getCellAt(x, y));
}

Spreadsheet::Spreadsheet(size_t width, size_t height)
    : m_id { ms_counter++ }, m_width { std::min(width, MaxHeight) },
      m_height { std::max(height, MaxHeight) } {
    std::cout << "普通的构造函数" << std::endl;
    m_cells = new SpreadsheetCell *[m_width];
    for (size_t i { 0 }; i < m_width; ++i) {
        m_cells[i] = new SpreadsheetCell[m_height];
    }
}

// 注意：
// 这是一个构造函数
Spreadsheet::Spreadsheet(Spreadsheet const &src)
    : Spreadsheet { src.m_width, src.m_height } {
    std::cout << "拷贝构造函数" << std::endl;
    for (size_t i { 0 }; i < m_width; ++i) {
        for (size_t j { 0 }; j < m_height; ++j) {
            m_cells[i][j] = src.m_cells[i][j];
        }
    }
}

Spreadsheet::Spreadsheet(Spreadsheet &&src) noexcept {
    // moveFrom(src);
    std::cout << "移动构造函数" << std::endl;
    ::swap(*this, src);
}

Spreadsheet::~Spreadsheet() {
    std::cout << "析构函数" << std::endl;
    for (size_t i { 0 }; i < m_width; ++i) {
        delete[] m_cells[i];
    }
    delete[] m_cells;
    m_cells = nullptr;
}

Spreadsheet &Spreadsheet::operator=(Spreadsheet const &rhs) {
    std::cout << "拷贝赋值运算符" << std::endl;
    // if (this == &rhs) {
    //     return *this;
    // }

    // // 释放原来的空间
    // for (size_t i { 0 }; i < m_width; ++i) {
    //     delete[] m_cells[i];
    // }
    // delete[] m_cells;
    // m_cells = nullptr;

    // m_width = rhs.m_width;
    // m_height = rhs.m_height;

    // // 重新分配
    // m_cells = new SpreadsheetCell *[m_width];
    // for (size_t i { 0 }; i < m_width; ++i) {
    //     m_cells[i] = new SpreadsheetCell[m_height];
    // }

    // // 拷贝数据
    // for (size_t i { 0 }; i < m_width; ++i) {
    //     for (size_t j { 0 }; j < m_height; ++j) {
    //         m_cells[i][j] = rhs.m_cells[i][j];
    //     }
    // }

    // return *this;

    /* ----------------------------------------------------------------------
     */
    Spreadsheet temp { rhs };
    swap(temp);
    return *this;
}

Spreadsheet &Spreadsheet::operator=(Spreadsheet &&rhs) noexcept {
    std::cout << "移动赋值运算符" << std::endl;
    ::swap(*this, rhs);
    return *this;
}

void Spreadsheet::setCellAt(size_t x, size_t y, SpreadsheetCell const &cell) {
    verifyCoordinate(x, y);
    m_cells[x][y] = cell;
}

// SpreadsheetCell &Spreadsheet::getCellAt(size_t x, size_t y) {
//     verifyCoordinate(x, y);
//     return m_cells[x][y];
// }

void Spreadsheet::swap(Spreadsheet &other) noexcept {
    std::swap(m_width, other.m_width);
    std::swap(m_height, other.m_height);
    std::swap(m_cells, other.m_cells);
}

// void Spreadsheet::cleanup() noexcept {
//     for (size_t i { 0 }; i < m_width; ++i) {
//         delete[] m_cells[i];
//     }
//     delete[] m_cells;
//     m_cells = nullptr;
// }

// void Spreadsheet::moveFrom(Spreadsheet &src) noexcept {
//     m_width = std::exchange(src.m_width, 0);
//     m_height = std::exchange(src.m_height, 0);
//     m_cells = std::exchange(src.m_cells, nullptr);
// }

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

void swap(Spreadsheet &first, Spreadsheet &second) noexcept {
    first.swap(second);
}

#endif
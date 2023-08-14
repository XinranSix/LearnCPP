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
    explicit SpreadsheetCell(double initialValue);
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

/* -------------------------------------------------------------------------- */

SpreadsheetCell SpreadsheetCell::operator-() const {
    return SpreadsheetCell { -getValue() };
}

TEST(重载算术运算符, 重载一元负号和一元正号运算符) {
    SpreadsheetCell c1 { 4 };
    SpreadsheetCell c3 { -c1 };
}

/* -------------------------------------------------------------------------- */

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

TEST(重载算术运算符, 重载重载递增和递减运算符) {
    SpreadsheetCell c1 { 4 };
    SpreadsheetCell c2 { 4 };
    c1++;
    ++c2;
}

/* -------------------------------------------------------------------------- */

TEST(重载算术运算符, 重载按位运算符和二元逻辑运算符) {}

/* -------------------------------------------------------------------------- */

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

TEST(重载算术运算符, 重载插入运算符和提取运算符) {}

/* -------------------------------------------------------------------------- */

template <typename T>
class Array {
public:
    Array();
    virtual ~Array();

    Array &operator=(Array const &rhs) = default;
    Array(Array const &src) = default;

    Array(Array &&src) noexcept;
    Array &operator=(Array &&rhs) noexcept;

    T const &getElementAt(size_t x) const;

    void setElementAt(size_t x, T const &value);

    size_t getSize() const noexcept;

public:
    T &operator[](size_t x);
    T const &operator[](size_t x) const;

private:
    static const size_t AllocSize { 4 };
    void resize(size_t newSize);
    T *m_elements { nullptr };
    size_t m_size { 0 };
};

template <typename T>
Array<T>::Array() {
    m_size = AllocSize;
    m_elements = new T[m_size] {};
}

template <typename T>
Array<T>::~Array() {
    delete[] m_elements;
    m_elements = nullptr;
}

template <typename T>
Array<T>::Array(Array &&src) noexcept
    : m_elements { std::exchange(src.m_elements, nullptr) },
      m_size { std::exchange(src.m_size, m_size) } {}

template <typename T>
Array<T> &Array<T>::operator=(Array<T> &&rhs) noexcept {
    if (*this == &rhs) {
        return *this;
    }
    delete[] m_elements;
    m_elements = std::exchange(rhs.m_elements, nullptr);
    m_size = std::exchange(rhs.m_size, 0);
    return *this;
}

template <typename T>
T const &Array<T>::getElementAt(size_t x) const {
    if (x >= m_size) {
        throw std::out_of_range { "" };
    }
    return m_elements[x];
}

template <typename T>
void Array<T>::setElementAt(size_t x, T const &value) {
    if (x >= m_size) {
        resize(x + AllocSize);
    }
    m_elements[x] = value;
}

template <typename T>
size_t Array<T>::getSize() const noexcept {
    return m_size;
}

template <typename T>
void Array<T>::resize(size_t newSize) {
    auto newArray { std::make_unique<T[]>(newSize) };

    for (size_t i { 0 }; i < m_size; ++i) {
        newArray[i] = m_elements[i];
    }
    delete[] m_elements;
    m_size = newSize;
    m_elements = newArray.release();
}

template <typename T>
T &Array<T>::operator[](size_t x) {
    if (x >= m_size) {
        resize(x + AllocSize);
    }
    return m_elements[x];
}

template <typename T>
T const &Array<T>::operator[](size_t x) const {
    if (x >= m_size) {
        throw std::out_of_range { "" };
    }
    return m_elements[x];
}

void printArray(Array<int> const &arr) {
    for (size_t i { 0 }; i < arr.getSize(); ++i) {
        std::cout << arr[i] << ' ';
    }
    std::cout << std::endl;
}

TEST(重载算术运算符, 重载下标运算符1) {
    Array<int> myArray;
    for (size_t i { 0 }; i < 10; ++i) {
        myArray[i] = 100;
    }
    for (size_t i { 0 }; i < 10; ++i) {
        std::cout << myArray[i] << ' ';
    }

    std::cout << std::endl;

    Array<Array<int>> a;
    a[2][4] = 24;
    std::cout << a[2][4] << std::endl;
}

TEST(重载算术运算符, 重载下标运算符2) {
    Array<int> myArray;
    for (size_t i { 0 }; i < 10; ++i) {
        myArray[i] = 100;
    }
    printArray(myArray);
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

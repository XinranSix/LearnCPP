#include <cstddef>
#include <deque>
#include <format>
#include <iostream>
#include <gtest/gtest.h>
#include <memory>
#include <optional>
#include <stdexcept>
#include <utility>
#include <vector>

template <typename Container>
concept ContainerType = requires(Container c) {
    c.resize(1);
    typename Container::value_type;
};

// template <typename T, ContainerType Container = std::vector<std::optional<T>>>
template <typename T, template <typename E, typename Allocator = std::allocator<E>>
                      class Container = std::vector>
class Grid {
public:
    explicit Grid(size_t width = DefalutWidth, size_t height = DefalutHeight);
    virtual ~Grid() = default;

    Grid(Grid const &) = default;
    Grid &operator=(Grid const &) = default;

    Grid(Grid &&) noexcept = default;
    Grid &operator=(Grid &&) noexcept = default;

    std::optional<T> &at(size_t x, size_t y);
    std::optional<T> const &at(size_t x, size_t y) const;

    size_t getHeight() const {
        return m_height;
    };

    size_t getWidth() const {
        return m_width;
    };

    static const size_t DefalutWidth { 10 };
    static const size_t DefalutHeight { 10 };

private:
    void verifyCoordinate(size_t x, size_t y) const;

    std::vector<Container<std::optional<T>>> m_cells;
    size_t m_width { 0 }, m_height { 0 };
};

/* -------------------------------------------------------------------------- */

template <typename T, template <typename E, typename Allocator = std::allocator<E>> class Container>
Grid<T, Container>::Grid(size_t width, size_t height) : m_width { width }, m_height { height } {
    m_cells.resize(m_width);
    for (auto &column : m_cells) {
        column.resize(m_height);
    }
}

template <typename T, template <typename E, typename Allocator = std::allocator<E>> class Container>
void Grid<T, Container>::verifyCoordinate(size_t x, size_t y) const {
    if (x >= m_width) {
        throw std::out_of_range { std::format("{} must be less than {}.", x, m_width) };
    }
    if (y >= m_height) {
        throw std::out_of_range { std::format("{} must be less than {}.", y, m_height) };
    }
}

template <typename T, template <typename E, typename Allocator = std::allocator<E>> class Container>
std::optional<T> &Grid<T, Container>::at(size_t x, size_t y) {
    return const_cast<std::optional<T> &>(std::as_const(*this).at(x, y));
}

template <typename T, template <typename E, typename Allocator = std::allocator<E>> class Container>
std::optional<T> const &Grid<T, Container>::at(size_t x, size_t y) const {
    verifyCoordinate(x, y);
    return m_cells[x][y];
}

TEST(深入了解模板, Grid类模板测试) {
    // Grid<int, std::vector<std::optional<int>>> myIntVectorGrid;
    // Grid<int, std::deque<std::optional<int>>> myIntDequeGrid;

    // myIntVectorGrid.at(3, 4) = 5;
    // std::cout << myIntVectorGrid.at(3, 4).value_or(0) << std::endl;

    // myIntDequeGrid.at(1, 2) = 3;
    // std::cout << myIntDequeGrid.at(1, 2).value_or(0) << std::endl;

    // Grid<int, std::vector<std::optional<int>>> grid2 { myIntVectorGrid };
    // grid2 = myIntVectorGrid;

    // Grid<int> myIntVectorGrid2;

    // Grid<int, double> test; // Error: 不符合约束
}

/* -------------------------------------------------------------------------- */

TEST(深入了解模板, typename_typename参数) {
    Grid<int, std::vector> myGrid;
    myGrid.at(1, 2) = 3;
    std::cout << myGrid.at(1, 2).value_or(0) << std::endl;
    Grid<int, std::vector> myGrid2 { myGrid };
    Grid<int, std::deque> myDequeGrid;
}

/* -------------------------------------------------------------------------- */

TEST(深入了解模板, 类模板部分特例化) {
    
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

#include <iostream>
#include <gtest/gtest.h>
#include <memory>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>
#include <format>

/* -------------------------------------------------------------------------- */

class GamePiece {
public:
    virtual ~GamePiece() = default;
    virtual std::unique_ptr<GamePiece> clone() const = 0;
};

/* -------------------------------------------------------------------------- */

class ChessPiece : public GamePiece {
public:
    std::unique_ptr<GamePiece> clone() const override {
        return std::make_unique<ChessPiece>(*this);
    }
};

/* -------------------------------------------------------------------------- */

class GameBoard {
public:
    explicit GameBoard(size_t width = DefaultWidth,
                       size_t height = DefaultHeight);
    GameBoard(GameBoard const &src);
    virtual ~GameBoard() = default;
    GameBoard &operator=(GameBoard const &rhs);

    GameBoard(GameBoard &&src) noexcept = default;
    GameBoard &operator=(GameBoard &src) noexcept = default;

    std::unique_ptr<GamePiece> &at(size_t x, size_t y);
    std::unique_ptr<GamePiece> const &at(size_t x, size_t y) const;

    size_t getHeight() const {
        return m_height;
    }

    size_t getWidth() const {
        return m_width;
    };

    static const size_t DefaultWidth { 10 };
    static const size_t DefaultHeight { 10 };

    void swap(GameBoard &other) noexcept;

private:
    void verifyCoordinate(size_t x, size_t y) const;

    std::vector<std::vector<std::unique_ptr<GamePiece>>> m_cells;
    size_t m_width { 0 }, m_height { 0 };
};

GameBoard::GameBoard(size_t width, size_t height)
    : m_width { width }, m_height { height } {
    m_cells.resize(m_width);
    for (auto &column : m_cells) {
        column.resize(m_height);
    }
}

GameBoard::GameBoard(GameBoard const &src)
    : GameBoard { src.m_width, src.m_height } {
    for (size_t i { 0 }; i < m_width; ++i) {
        for (size_t j { 0 }; j < m_height; ++j) {
            if (src.m_cells[i][j]) {
                m_cells[i][j] = src.m_cells[i][j]->clone();
            }
        }
    }
}

void GameBoard::verifyCoordinate(size_t x, size_t y) const {
    if (x >= m_width) {
        throw std::out_of_range { std::format("{} must be less than {}.", x,
                                              m_width) };
    }
    if (y > m_height) {
        throw std::out_of_range { std::format("{} must be less than {}.", y,
                                              m_height) };
    }
}

void GameBoard::swap(GameBoard &other) noexcept {
    std::swap(m_width, other.m_width);
    std::swap(m_height, other.m_height);
    std::swap(m_cells, other.m_cells);
}

GameBoard &GameBoard::operator=(GameBoard const &rhs) {
    GameBoard temp { rhs };
    swap(temp);
    return *this;
}

std::unique_ptr<GamePiece> &GameBoard::at(size_t x, size_t y) {
    verifyCoordinate(x, y);
    return m_cells[x][y];
}

std::unique_ptr<GamePiece> const &GameBoard::at(size_t x, size_t y) const {
    return const_cast<std::unique_ptr<GamePiece> &>(
        std::as_const(*this).at(x, y));
}

void swap(GameBoard &first, GameBoard &second) noexcept {
    first.swap(second);
}

/* -------------------------------------------------------------------------- */

template <typename T = int, size_t WIDTH = 10, size_t HEIGHT = 10>
class Grid {
public:
    explicit Grid(size_t width = DefalutWidth, size_t height = DefalutHeight);
    virtual ~Grid() = default;

    Grid(Grid const &src) = default;
    Grid &operator=(Grid const &rhs) = default;

    Grid(Grid &&src) noexcept = default;
    Grid &operator=(Grid &&rhs) noexcept = default;

    std::optional<T> &at(size_t x, size_t y);
    std::optional<T> const &at(size_t x, size_t y) const;

    size_t getHeight() const {
        return m_height;
    }

    size_t getWidth() const {
        return m_width;
    }

    static const size_t DefalutWidth { 10 };
    static const size_t DefalutHeight { 10 };

public:
    template <typename E, size_t WIDTH2, size_t HEIGHT2>
    Grid(Grid<E, WIDTH2, HEIGHT2> const &src);

    template <typename E, size_t WIDTH2, size_t HEIGHT2>
    Grid<T> &operator=(Grid<E, WIDTH2, HEIGHT2> const &rhs);

    void swap(Grid &other) noexcept;

private:
    void verifyCoordinate(size_t x, size_t y);

    std::vector<std::vector<std::optional<T>>> m_cells;
    size_t m_width { 0 }, m_height { 0 };
};

template <typename T, size_t WIDTH, size_t HEIGHT>
Grid<T, WIDTH, HEIGHT>::Grid(size_t width, size_t height)
    : m_width { width }, m_height { height } {
    m_cells.resize(m_width);
    for (auto &column : m_cells) {
        column.resize(m_height);
    }
}

template <typename T, size_t WIDTH, size_t HEIGHT>
void Grid<T, WIDTH, HEIGHT>::verifyCoordinate(size_t x, size_t y) {
    if (x >= WIDTH) {
        throw std::out_of_range { std::format("{} must be less than {}.", x,
                                              m_width) };
    }
    if (y >= HEIGHT) {
        throw std::out_of_range { std::format("{} must be less than {}", y,
                                              m_height) };
    }
}

template <typename T, size_t WIDTH, size_t HEIGHT>
std::optional<T> &Grid<T, WIDTH, HEIGHT>::at(size_t x, size_t y) {
    verifyCoordinate(x, y);
    return m_cells[x][y];
}

template <typename T, size_t WIDTH, size_t HEIGHT>
std::optional<T> const &Grid<T, WIDTH, HEIGHT>::at(size_t x, size_t y) const {
    return const_cast<std::optional<T> &>(std::as_const(*this).at(x, y));
}

template <typename T, size_t WIDTH, size_t HEIGHT>
template <typename E, size_t WIDTH2, size_t HEIGHT2>
Grid<T, WIDTH, HEIGHT>::Grid(Grid<E, WIDTH2, HEIGHT2> const &src)
    : Grid { src.getWidth(), src.getHeight() } {
    for (size_t i { 0 }; i < m_width; ++i) {
        for (size_t j { 0 }; j < m_height; ++j) {
            if (i < WIDTH2 && j < HEIGHT2) {
                m_cells[i][j] = src.at(i, j);
            } else {
                m_cells[i][j].reset();
            }
        }
    }
}

template <typename T, size_t WIDTH, size_t HEIGHT>
template <typename E, size_t WIDTH2, size_t HEIGHT2>
Grid<T> &
Grid<T, WIDTH, HEIGHT>::operator=(Grid<E, WIDTH2, HEIGHT2> const &rhs) {
    Grid<T, WIDTH, HEIGHT> temp { rhs };
    swap(temp);
    return *this;
}

template <typename T, size_t WIDTH, size_t HEIGHT>
void Grid<T, WIDTH, HEIGHT>::swap(Grid &other) noexcept {
    std::swap(m_cells, other.m_cells);
}

/* -------------------------------------------------------------------------- */

TEST(类模板, 测试1) {
    GameBoard chessBoard { 8, 8 };
    auto pawn { std::make_unique<ChessPiece>() };
    chessBoard.at(0, 0) = std::move(pawn);
    chessBoard.at(0, 1) = std::make_unique<ChessPiece>();
    chessBoard.at(0, 1) = nullptr;
}

TEST(类模板, 测试2) {
    Grid<int, 10, 10> myGrid;
    Grid<int, 10, 10> anotherGrid;
    myGrid.at(2, 3) = 42;
    anotherGrid = myGrid;
    std::cout << anotherGrid.at(2, 3).value_or(0) << std::endl;
}

TEST(类模板, CTDA) {
    std::pair<int, double> pair1 { 1, 2.3 };
    auto pair2 { std::make_pair(1, 2.3) };
    std::pair pair3 { 1, 2.3 };
}

template <typename T>
struct X {
    X(T const &t) : m_context(t) {
    }

    T const &getContent() const {
        return m_context;
    }

private:
    T m_context;
};

X(const char *) -> X<std::string>;

TEST(类模板, 用户定义的推导规则) {
    std::string myString { "Hello World!" };
    X x1 { myString };

    X x2 { "hyt" };
}

template <>
class Grid<const char *> {
public:
    explicit Grid(size_t width = DefalutWidth, size_t height = DefalutHeight);
    virtual ~Grid() = default;

    Grid(Grid const &src) = default;
    Grid &operator=(Grid const &rhs) = default;

    Grid(Grid &&src) noexcept = default;
    Grid &operator=(Grid &&rhs) noexcept = default;

    std::optional<std::string> &at(size_t x, size_t y);
    std::optional<std::string> const &at(size_t x, size_t y) const;

    size_t getHeight() const {
        return m_height;
    }

    size_t getWidth() const {
        return m_width;
    }

    static const size_t DefalutWidth { 10 };
    static const size_t DefalutHeight { 10 };

public:
    template <typename E, size_t WIDTH2, size_t HEIGHT2>
    Grid(Grid<E, WIDTH2, HEIGHT2> const &src);

    template <typename E, size_t WIDTH2, size_t HEIGHT2>
    Grid<std::string> &operator=(Grid<E, WIDTH2, HEIGHT2> const &rhs);

    void swap(Grid &other) noexcept;

private:
    void verifyCoordinate(size_t x, size_t y);

    std::vector<std::vector<std::optional<std::string>>> m_cells;
    size_t m_width { 0 }, m_height { 0 };
};

Grid<const char *>::Grid(size_t width, size_t height)
    : m_width { width }, m_height { height } {
    m_cells.resize(m_width);
    for (auto &column : m_cells) {
        column.resize(m_height);
    }
}

void Grid<const char *>::verifyCoordinate(size_t x, size_t y) {
    if (x >= m_width) {
        throw std::out_of_range { std::format("{} must be less than {}.", x,
                                              m_width) };
    }
    if (y >= m_height) {
        throw std::out_of_range { std::format("{} must be less than {}", y,
                                              m_height) };
    }
}

std::optional<std::string> &Grid<const char *>::at(size_t x, size_t y) {
    verifyCoordinate(x, y);
    return m_cells[x][y];
}

std::optional<std::string> const &Grid<const char *>::at(size_t x,
                                                         size_t y) const {
    return const_cast<std::optional<std::string> &>(
        std::as_const(*this).at(x, y));
}

TEST(类模板, 类模板的特化) {
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

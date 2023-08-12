#include <iostream>
#include <gtest/gtest.h>
#include <memory>
#include <stdexcept>
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

template <typename T>
class Grid {
public:
    explicit Grid(size_t width = DefalutWidth, size_t height = DefalutHeight);
    virtual ~Grid() = default;

    Grid(Grid const &src) = default;
    Grid &operator=(Grid const &rhs) = default;

    Grid(Grid &&src) = default;
    Grid &operator=(Grid &&rhs) = default;

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

private:
    void verifyCoordinate(size_t x, size_t y);

    std::vector<std::vector<std::optional<T>>> m_cells;
    size_t m_width { 0 }, m_height { 0 };
};

TEST(类模板, 测试1) {
    GameBoard chessBoard { 8, 8 };
    auto pawn { std::make_unique<ChessPiece>() };
    chessBoard.at(0, 0) = std::move(pawn);
    chessBoard.at(0, 1) = std::make_unique<ChessPiece>();
    chessBoard.at(0, 1) = nullptr;
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

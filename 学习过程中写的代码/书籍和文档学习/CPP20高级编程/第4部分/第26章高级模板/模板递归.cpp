#include <cstddef>
#include <iostream>
#include <vector>

// template <typename T>
// class OneDGrid {
// public:
//     explicit OneDGrid(size_t size = DefaultSize) {
//         resize(size);
//     }

//     virtual ~OneDGrid() = default;

//     T &operator[](size_t x) {
//         return m_elements[x];
//     }

//     T const &operator[](size_t x) const {
//         return m_elements[x];
//     }

//     void resize(size_t newSize) {
//         m_elements.resize(newSize);
//     }

//     size_t getSize() const {
//         return m_elements.size();
//     }

//     static const size_t DefaultSize { 10 };

// private:
//     std::vector<T> m_elements;
// };

// N 维网格

template <typename T, size_t N>
class NDGrid {
public:
    explicit NDGrid(size_t size = DefaultSize) {
        resize(size);
    }

    NDGrid<T, N - 1> &operator[](size_t x) {
        return m_elements[x];
    }

    NDGrid<T, N - 1> const &operator[](size_t x) const {
        return m_elements[x];
    }

    void resize(size_t newSize) {
        m_elements.resize(newSize);
        for (auto &element : m_elements) {
            element.resize(newSize);
        }
    }

    static const size_t DefaultSize { 10 };

private:
    std::vector<NDGrid<T, N - 1>> m_elements;
};

template <typename T>
class NDGrid<T, 1> {
public:
    explicit NDGrid(size_t size = DefaultSize) {
        resize(size);
    }

    T &operator[](size_t x) {
        return m_elements[x];
    }

    T const &operator[](size_t x) const {
        return m_elements[x];
    }

    void resize(size_t newSize) {
        m_elements.resize(newSize);
    }

    size_t getSize() const {
        return m_elements.size();
    }

    static const size_t DefaultSize { 10 };

private:
    std::vector<T> m_elements;
};

int main(int argc, char *argv[]) {

    // OneDGrid<int> singleDGrid;
    // OneDGrid<OneDGrid<int>> twoDGrid;
    // OneDGrid<OneDGrid<OneDGrid<int>>> threeDGrid;

    // singleDGrid[3] = 5;
    // twoDGrid[3][3] = 5;
    // threeDGrid[3][3][3] = 5;

    /* ---------------------------------------------------------------------- */
    NDGrid<int, 3> my3DGrid { 4 };
    my3DGrid[2][1][2] = 5;
    my3DGrid[1][1][1] = 5;
    std::cout << my3DGrid[2][1][2] << std::endl;

    return 0;
}

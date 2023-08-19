#ifndef YT_GRAPH_NODES_HPP
#define YT_GRAPH_NODES_HPP

#include <cstddef>
#include <set>

namespace yt {

    template <typename T>
    class directed_graph;

    template <typename T>
    class graph_node {
    public:
        // 从给定值构造一个 graph_node
        graph_node(directed_graph<T> *graph, T const &t);
        graph_node(directed_graph<T> *graph, T &&t);

        // 返回节点存储值的引用
        [[nodiscard]] T &value() noexcept;
        [[nodiscard]] T const &value() const noexcept;

        // C++ 20 默认的 operator==
        bool operator==(graph_node const &) const = default;

    private:
        friend class directed_graph<T>;

        // 指向该节点所在图的指针
        directed_graph<T> *m_graph;

        // 邻接表的类型别名，实际上是一个 set
        using adjacency_list_type = std::set<size_t>;

        // 返回当前节点邻接表的的引用
        [[nodiscard]] adjacency_list_type &get_adjacent_nodes_indices();
        [[nodiscard]] adjacency_list_type const &get_adjacent_nodes_indices() const;

        T m_data;
        adjacency_list_type m_adjacentNodeIndices;
    };

    /* ---------------------------------------------------------------------- */

    template <typename T>
    graph_node<T>::graph_node(directed_graph<T> *graph, T const &t)
        : m_graph { graph }, m_data { t } {}

    template <typename T>
    graph_node<T>::graph_node(directed_graph<T> *graph, T &&t)
        : m_graph { graph }, m_data { std::move(t) } {}

    template <typename T>
    T &graph_node<T>::value() noexcept {
        return m_data;
    }

    template <typename T>
    T const &graph_node<T>::value() const noexcept {
        return m_data;
    }

    template <typename T>
    typename graph_node<T>::adjacency_list_type &graph_node<T>::get_adjacent_nodes_indices() {
        return m_adjacentNodeIndices;
    }

    template <typename T>
    typename graph_node<T>::adjacency_list_type const &
    graph_node<T>::get_adjacent_nodes_indices() const {
        return m_adjacentNodeIndices;
    }

} // namespace yt

#endif

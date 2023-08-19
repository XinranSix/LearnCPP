#ifndef YT_DIRECTED_GRAPH_HPP
#define YT_DIRECTED_GRAPH_HPP

#include <algorithm>
#include <cstddef>
#include <format>
#include <iterator>
#include <set>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>
#include "graph_node.hpp"

namespace yt {

    template <typename T>
    class directed_graph {
    public:
        // 类型别名
        using value_type = T;
        using reference = value_type &;
        using const_reference = const value_type &;
        using size_type = size_t;
        using difference_type = ptrdiff_t;

    public:
        // 插入节点的值要求在原图中不存在
        // 插入成功返回 true
        // 如果原图中存在值为 node_value 的节点
        // 返回 false
        bool insert(T const &node_value);
        bool insert(T &&node_value);

        // Returns true if the given node_value was erased, false otherwise.
        bool erase(T const &node_value);

        // Returns true if the edge was successfully created, false otherwise.
        bool insert_edge(T const &from_node_value, T const &to_node_value);

        // Returns true if the give edge was erased, false otherwise.
        bool erase_edge(T const &from_node_value, T const &to_node_value);

        // Removes all nodes from the graph.
        void clear() noexcept;

        // Returns a reference to the node with given index.
        // No bounds checking is done.
        T &operator[](size_t index);
        T const &operator[](size_t index) const;

        // Two directed graphs are equal if they have the same nodes and edges.
        // The order in which the nodes and edges have been added does not
        // affect equality.
        bool operator==(directed_graph const &rgs) const;
        bool operator!=(directed_graph const &rhs) const;

        // Swaps all nodes between this graph and the given graph.
        void swap(directed_graph &other_graph) noexcept;

        // Returns the number of nodes in the graph.
        [[nodiscard]] size_t size() const noexcept;

        // Returns a set with the adjacent nodes of a given node.
        // If the given node does not exist, an empty set is returned.
        [[nodiscard]] std::set<T> get_adjacent_nodes_values(T const &node_value) const;

    private:
        using nodes_container_type = std::vector<graph_node<T>>;
        nodes_container_type m_nodes;

    private:
        // Helper method to return an iterator to the given node, or the end iterator if the given
        // node is not in the graph.
        typename nodes_container_type::iterator findNode(T const &node_value);
        typename nodes_container_type::const_iterator findNode(T const &node_value) const;

        size_t
        get_index_of_node(typename nodes_container_type::const_iterator const &node) const noexcept;

        void remove_all_links_to(typename nodes_container_type::const_iterator node_iter);

        std::set<T>
        get_adjacent_nodes_values(typename graph_node<T>::adjacency_list_type const &indices) const;
    };

    /* ---------------------------------------------------------------------- */
    // 辅助方法, 查找指定值的节点
    template <typename T>
    typename directed_graph<T>::nodes_container_type::iterator
    directed_graph<T>::findNode(T const &node_value) {
        return std::find_if(std::begin(m_nodes), std::end(m_nodes),
                            [&node_value](auto const &node) { return node.value() == node_value; });
    }

    template <typename T>
    typename directed_graph<T>::nodes_container_type::const_iterator
    directed_graph<T>::findNode(T const &node_value) const {
        return const_cast<directed_graph<T> *>(this)->findNode(node_value);
    }

    // 辅助方法，查找给定值在 vector 中的索引
    template <typename T>
    size_t directed_graph<T>::get_index_of_node(
        typename directed_graph<T>::nodes_container_type::const_iterator const &node)
        const noexcept {
        const auto index { std::distance(std::cbegin(m_nodes), node) };
        return static_cast<size_t>(index);
    }

    template <typename T>
    void directed_graph<T>::remove_all_links_to(
        typename directed_graph<T>::nodes_container_type::const_iterator node_iter) {
        const size_t node_index { get_index_of_node(node_iter) };

        for (auto &&node : m_nodes) {
            auto &adjacencyIndices { node.get_adjacent_nodes_indices() };

            adjacencyIndices.erase(node_index);

            std::vector<size_t> indices(std::begin(adjacencyIndices), std::end(adjacencyIndices));
            std::for_each(std::begin(indices), std::end(indices), [node_index](size_t &index) {
                if (index > node_index) {
                    --index;
                }
            });
            adjacencyIndices.clear();
            adjacencyIndices.insert(std::begin(indices), std::end(indices));
        }
    }

    template <typename T>
    std::set<T> directed_graph<T>::get_adjacent_nodes_values(
        typename graph_node<T>::adjacency_list_type const &indices) const {
        std::set<T> values;
        for (auto &&index : indices) {
            values.insert(m_nodes[index].value());
        }
        return values;
    }

    /* ------------------------------------------------------------------ */
    // 插入节点
    template <typename T>
    bool directed_graph<T>::insert(T const &node_value) {
        T copy { node_value };
        return insert(std::move(copy));
    }

    template <typename T>
    bool directed_graph<T>::insert(T &&node_value) {
        auto iter { findNode(node_value) };
        if (iter != std::end(m_nodes)) {
            return false;
        }
        m_nodes.emplace_back(this, std::move(node_value));
        return true;
    }

    /* ---------------------------------------------------------------------- */
    // 插入边
    template <typename T>
    bool directed_graph<T>::insert_edge(T const &from_node_value, T const &to_node_value) {
        const auto from { findNode(from_node_value) };
        const auto to { findNode(to_node_value) };

        if (from == std::end(m_nodes) || to == std::end(m_nodes)) {
            return false;
        }
        const size_t to_index { get_index_of_node(to) };
        return from->get_adjacent_nodes_indices().insert(to_index).second;
    }

    /* ---------------------------------------------------------------------- */
    // 删除节点
    template <typename T>
    bool directed_graph<T>::erase(T const &node_value) {
        auto iter { findNode(node_value) };
        if (iter == std::end(m_nodes)) {
            return false;
        }
        remove_all_links_to(iter);
        m_nodes.erase(iter);
        return true;
    }

    /* ---------------------------------------------------------------------- */
    // 删除边
    template <typename T>
    bool directed_graph<T>::erase_edge(T const &from_node_value, T const &to_node_value) {
        const auto from { findNode(from_node_value) };
        const auto to { findNode(to_node_value) };

        if (from == std::end(m_nodes) || to == std::end(m_nodes)) {
            return false;
        }

        const size_t to_index { get_index_of_node(to) };
        from->get_adjacent_nodes_indices().erase(to_index);
        return true;
    }

    /* ---------------------------------------------------------------------- */
    // 清空节点
    template <typename T>
    void directed_graph<T>::clear() noexcept {
        m_nodes.clear();
    }

    /* ---------------------------------------------------------------------- */
    // 交换图
    template <typename T>
    void directed_graph<T>::swap(directed_graph &other_graph) noexcept {
        m_nodes.swap(other_graph.m_nodes);
    }

    /* ---------------------------------------------------------------------- */
    // 访问节点
    template <typename T>
    T &directed_graph<T>::operator[](size_t index) {
        return m_nodes[index].value();
    }

    template <typename T>
    T const &directed_graph<T>::operator[](size_t index) const {
        return m_nodes[index].value();
    }

    /* ---------------------------------------------------------------------- */
    // 比较图
    template <typename T>
    bool directed_graph<T>::operator==(directed_graph const &rhs) const {
        if (m_nodes.size() != rhs.m_nodes.size()) {
            return false;
        }

        for (auto &&node : m_nodes) {
            const auto rhsNodeIter { rhs.findNode(node.value()) };
            if (rhsNodeIter == std::end(rhs.m_nodes)) {
                return false;
            }

            const auto adjacent_values_lsh { get_adjacent_nodes_values(
                node.get_adjacent_nodes_indices()) };
            const auto adjacent_values_rsh { rhs.get_adjacent_nodes_values(
                rhsNodeIter->get_adjacent_nodes_indices()) };
            if (adjacent_values_lsh != adjacent_values_rsh) {
                return false;
            }
        }
        return true;
    }

    template <typename T>
    bool directed_graph<T>::operator!=(directed_graph const &rhs) const {
        return !(*this == rhs);
    }

    /* ---------------------------------------------------------------------- */
    // 获取相邻节点
    template <typename T>
    std::set<T> directed_graph<T>::get_adjacent_nodes_values(T const &node_value) const {
        auto iter { findNode(node_value) };
        if (iter == std::end(m_nodes)) {
            return std::set<T> {};
        }
        return get_adjacent_nodes_values(iter->get_adjacent_nodes_indices());
    }

    /* ---------------------------------------------------------------------- */
    // 查询图的大小
    template <typename T>
    size_t directed_graph<T>::size() const noexcept {
        return m_nodes.size();
    }

    /* ---------------------------------------------------------------------- */
    // 打印图
    template <typename T>
    std::wstring to_dot(directed_graph<T> const &graph, std::wstring_view graph_name) {
        std::wstringstream wss;
        wss << std::format(L"digraph {} {{", graph_name.data()) << std::endl;
        for (size_t index { 0 }; index < graph.size(); ++index) {
            auto const &node_value { graph[index] };
            const auto adjacent_nodes { graph.get_adjacent_nodes_values(node_value) };
            if (adjacent_nodes.empty()) {
                wss << node_value << std::endl;
            } else {
                for (auto &&node : adjacent_nodes) {
                    wss << std::format(L"{} -> {}", node_value, node) << std::endl;
                }
            }
        }
        wss << "}" << std::endl;
        return wss.str();
    }

} // namespace yt

#endif

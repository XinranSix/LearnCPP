#include <algorithm>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>
#include <cstddef>
#include <format>
#include <iostream>
#include <gtest/gtest.h>
#include <iterator>
#include <set>

template <typename InputIterator, typename OutputIterator, typename Predicate>
OutputIterator find_all(InputIterator first, InputIterator last, OutputIterator dest,
                        Predicate pred) {
    while (first != last) {
        if (pred(*first)) {
            *dest = first;
            ++dest;
        }
        ++first;
    }
    return dest;
}

TEST(拓展标准库, find_all算法) {
    std::vector vec { 3, 4, 5, 4, 5, 6, 5, 8 };
    std::vector<std::vector<int>::iterator> matches;

    find_all(begin(vec), end(vec), std::back_inserter(matches), [](int i) { return i == 5; });

    std::cout << std::format("Found {} mathing elements: ", matches.size()) << std::endl;
    for (auto const &it : matches) {
        std::cout << *it << " at position " << (it - cbegin(vec)) << std::endl;
    }
}

namespace yt {
    template <typename T>
    class graph_node;

    // diected_graph
    template <typename T>
    class directed_graph {
    public:
        bool insert(T const &node_value);
        bool insert(T &&node_value);

        bool earse(T const &node_value);

        bool insert_edge(T const &from_node_value, T const &to_node_value);

        bool erase_edge(T const &from_node_value, T &to_node_value);

        void clear() noexcept;

        T &operator[](size_t index);
        T const &operator[](size_t index) const;

        bool operator==(directed_graph const &rhs) const;
        bool operator!=(directed_graph const &rhs) const;

        void swap(directed_graph &other_graph) noexcept;

        [[nodiscard]] size_t size() const noexcept;

        [[nodiscard]] std::set<T> get_adjacent_nodes_values(T const &node_value) const;

    private:
        using nodes_container_type = std::vector<graph_node<T>>;
        nodes_container_type m_nodes;

        typename nodes_container_type::iterator findNode(T const &node_value);
        typename nodes_container_type::const_iterator findNode(T const &node_value) const;

        size_t get_index_of_node(nodes_container_type::const_iterator const &node) const noexcept;

        void remove_all_links_to(nodes_container_type::const_iterator node_iter);

        std::set<T>
        get_adjacent_nodes_values(typename graph_node<T>::adjacency_list_type const &indices) const;
    };

    template <typename T>
    size_t directed_graph<T>::size() const noexcept {
        return m_nodes.size();
    }

    template <typename T>
    std::set<T> directed_graph<T>::get_adjacent_nodes_values(T const &node_value) const {
        auto iter { findNode(node_value) };
        if (iter == std::end(m_nodes)) {
            return std::set<T>();
        }
        return get_adjacent_nodes_values(iter->get_adjacent_nodes_indices());
    }

    template <typename T>
    bool directed_graph<T>::operator!=(directed_graph const &rhs) const {
        return !(*this == rhs);
    }

    template <typename T>
    std::set<T> directed_graph<T>::get_adjacent_nodes_values(
        typename graph_node<T>::adjacency_list_type const &indices) const {
        std::set<T> values;
        for (auto &&index : indices) {
            values.insert(m_nodes[index].value());
            return values;
        }
    }

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

            const auto adjacent_value_lhs { get_adjacent_nodes_values(
                node.get_adjacent_nodes_indices()) };
            const auto adjacent_values_rhs { rhs.get_adjacent_nodes_values(
                rhsNodeIter->get_adjacent_nodes_indices()) };
            if (adjacent_value_lhs != adjacent_values_rhs) {
                return false;
            }
        }
        return true;
    }

    template <typename T>
    T &directed_graph<T>::operator[](size_t index) {
        return m_nodes[index].value();
    }

    template <typename T>
    T const &directed_graph<T>::operator[](size_t index) const {
        return m_nodes[index].value();
    }

    template <typename T>
    void directed_graph<T>::swap(directed_graph &other_graph) noexcept {
        m_nodes.swap(other_graph.m_nodes);
    }

    template <typename T>
    void directed_graph<T>::clear() noexcept {
        m_nodes.clear();
    }

    template <typename T>
    bool directed_graph<T>::erase_edge(T const &from_node_value, T &to_node_value) {
        const auto from { findNode(from_node_value) };
        const auto to { findNode(to_node_value) };

        if (from == std::end(m_nodes) || to == std::end(m_nodes)) {
            return false;
        }
        const size_t to_index { get_index_of_node(to) };
        from->get_adjacent_nodes_indices().erase(to_index);
        return true;
    }

    template <typename T>
    bool directed_graph<T>::earse(T const &node_value) {
        auto iter { findNode(node_value) };
        if (iter == std::end(m_nodes)) {
            return false;
        }
        remove_all_links_to(iter);
        m_nodes.erase(iter);
        return true;
    }

    template <typename T>
    void directed_graph<T>::remove_all_links_to(nodes_container_type::const_iterator node_iter) {
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
    size_t directed_graph<T>::get_index_of_node(
        typename nodes_container_type::const_iterator const &node) const noexcept {
        const auto index { std::distance(std::cbegin(m_nodes), node) };
        return static_cast<size_t>(index);
    }

    template <typename T>
    bool directed_graph<T>::insert_edge(T const &from_node_value, T const &to_node_value) {
        const auto from { findNode(from_node_value) };
        const auto to { findNode(to_node_value) };

        if (from == std::end(m_nodes) || to == std::end(m_nodes)) {
            return false;
        }
        const size_t to_index { get_index_of_node(to) };
        // return from->get_adjacent_node_indices().insert(to_index).second;
        return from->m_adjacentNodeIndices.insert(to_index).second;
    // }
    }

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
} // namespace yt

namespace yt {
    // graph_node 类模板
    template <typename T>
    class graph_node {
    public:
        graph_node(directed_graph<T> *graph, T const &t);
        graph_node(directed_graph<T> *graph, T &&t);

        [[nodiscard]] T &value() noexcept;
        [[nodiscard]] T const &value() const noexcept;

        bool operator==(graph_node const &) const = default;

    private:
        friend class directed_graph<T>;

        directed_graph<T> *m_graph;

        using adjacency_list_type = std::set<size_t>;
        [[nodiscard]] adjacency_list_type &get_adjacent_nodes_indices();
        [[nodiscard]] adjacency_list_type const &get_adjacent_node_indices() const;

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
    graph_node<T>::get_adjacent_node_indices() const {
        return m_adjacentNodeIndices;
    }

}; // namespace yt

namespace yt {
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

TEST(拓展标准库, 基本的有向图) {
    using namespace yt;
    directed_graph<int> graph;

    graph.insert(11);
    graph.insert(22);
    graph.insert(33);
    graph.insert(44);
    graph.insert(55);
    graph.insert_edge(11, 33);
    graph.insert_edge(22, 33);
    graph.insert_edge(22, 44);
    graph.insert_edge(22, 55);
    graph.insert_edge(33, 44);
    graph.insert_edge(44, 55);
    std::wcout << to_dot(graph, L"Graph1");
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

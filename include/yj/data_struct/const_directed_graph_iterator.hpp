#ifndef YT_CONST_DIRECTED_GRAPH_ITERATOR
#define YT_CONST_DIRECTED_GRAPH_ITERATOR

#include "directed_graph.hpp"
#include <cstddef>
#include <iterator>

namespace yt {
    template <typename DirectedGraph>
    class const_directed_graph_iterator {
    public:
        using value_type = typename DirectedGraph::value_type;
        using difference_type = ptrdiff_t;
        using iterator_category = std::bidirectional_iterator_tag;
        using pointer = const value_type *;
        using reference = const value_type &;
        using iterator_type = typename DirectedGraph::nodes_container_type::const_iterator;

        // Bidirectional iterators must supply default constructor.
        // Using an iterator constructed with the default constructor is undefined, so it doesn't
        // matter how it's initialized.
        const_directed_graph_iterator() = default;

        // No transfer of ownership of graph
        const_directed_graph_iterator(iterator_type it, const DirectedGraph *graph);

        reference operator*() const;

        // Return type must be something to whice -> can be applied.
        // So, return a pointer.
        pointer operator->() const;
        const_directed_graph_iterator &operator++();
        const_directed_graph_iterator operator++(int);

        const_directed_graph_iterator &operator--();
        const_directed_graph_iterator operator--(int);

        // C++ 20 defaulted operator==
        bool operator==(const_directed_graph_iterator const &) const = default;

    protected:
        friend class directed_graph<value_type>;

        iterator_type m_nodeIterator;
        const DirectedGraph *m_graph { nullptr };

        void increment();
        void decrement();
    };

    /* ---------------------------------------------------------------------- */
    template <typename DirectedGraph>
    const_directed_graph_iterator<DirectedGraph>::const_directed_graph_iterator(
        iterator_type it, const DirectedGraph *graph)
        : m_nodeIterator { it }, m_graph { graph } {}

    /* ---------------------------------------------------------------------- */

    // Return a reference to the actual element.
    template <typename DirectedGraph>
    const_directed_graph_iterator<DirectedGraph>::reference
    const_directed_graph_iterator<DirectedGraph>::operator*() const {
        return m_nodeIterator->value();
    }

    // Return a pointer to the actual element, so the complier can
    // apply -> to it to access the actual desired filed.
    template <typename DirectedGraph>
    const_directed_graph_iterator<DirectedGraph>::pointer
    const_directed_graph_iterator<DirectedGraph>::operator->() const {
        return &(m_nodeIterator->value());
    }

    /* ---------------------------------------------------------------------- */

    template <typename DirectedGraph>
    const_directed_graph_iterator<DirectedGraph> &
    const_directed_graph_iterator<DirectedGraph>::operator++() {
        increment();
        return *this;
    }

    template <typename DirectedGraph>
    const_directed_graph_iterator<DirectedGraph>
    const_directed_graph_iterator<DirectedGraph>::operator++(int) {
        auto oldIt { *this };
        increment();
        return oldIt;
    }

    template <typename DirectedGraph>
    const_directed_graph_iterator<DirectedGraph> &
    const_directed_graph_iterator<DirectedGraph>::operator--() {
        decrement();
        return *this;
    }

    template <typename DirectedGraph>
    const_directed_graph_iterator<DirectedGraph>
    const_directed_graph_iterator<DirectedGraph>::operator--(int) {
        auto oldIt { *this };
        decrement();
        return oldIt;
    }

    /* ---------------------------------------------------------------------- */

    template <typename DirectedGraph>
    void const_directed_graph_iterator<DirectedGraph>::increment() {
        ++m_nodeIterator;
    }

    template <typename DirectedGraph>
    void const_directed_graph_iterator<DirectedGraph>::decrement() {
        --m_nodeIterator;
    }

} // namespace yt

#endif
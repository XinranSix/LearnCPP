#include <algorithm>
#include <cstdlib>
#include <fstream>
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
#include "yj/data_struct/directed_graph.hpp"
#include "yj/data_struct/graph_node.hpp"
#include "yj/data_struct/const_directed_graph_iterator.hpp"
#include "yj/data_struct/directed_graph_iterator.hpp"

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

TEST(拓展标准库, 基本的有向图) {

    std::wofstream wofs { "test.dot" };

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

    // graph.erase_edge(22, 44);
    // graph.erase(44);
    // wofs << to_dot(graph, L"Graph2");

    // std::cout << "Size: " << graph.size() << std::endl;
    // wofs.close();

    // system("dot -Tpng test.dot -o test.png");

    /* ---------------------------------------------------------------------- */

    auto [iter22, inserted] { graph.insert(22) };
    if (!inserted) {
        std::cout << "Duplicate element.\n";
    }

    for (auto iter { graph.begin() }; iter != graph.end(); ++iter) {
        std::cout << *iter << " ";
    }
    std::cout << std::endl;

    for (auto iter { std::cbegin(graph) }; iter != std::cend(graph); ++iter) {
        std::cout << *iter << " ";
    }
    std::cout << std::endl;

    for (auto &node : graph) {
        std::cout << node << " ";
    }
    std::cout << std::endl;

    auto result { std::find(std::begin(graph), std::end(graph), 22) };
    if (result != std::end(graph)) {
        std::cout << "Node 22 found." << std::endl;
    } else {
        std::cout << "Node 22 NOT found." << std::endl;
    }

    auto count { std::count_if(std::begin(graph), std::end(graph),
                               [](auto const &node) { return node > 22; }) };

    graph.erase(std::find(std::begin(graph), std::end(graph), 44));

    for (auto iter { graph.rbegin() }; iter != graph.rend(); ++iter) {
        std::cout << *iter << " ";
    }
    std::cout << std::endl;
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

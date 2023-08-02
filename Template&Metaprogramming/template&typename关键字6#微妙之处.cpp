#include <iostream>
#include <iterator>

template<typename Iterator>
struct categrory_index {

    template<long N>
    struct index {
        using type = char (&)[N];
    };

    int categroy(std::input_iterator_tag) {
        return sizeof(typename index<1>::type);
    }

    int category(std::forward_iterator_tag) {
        return sizeof(typename index<2>::type);
    }
};

template<>
template<long N>
struct categrory_index<int *>::index {
    using type = char (&)[N + 1];
};

int main(int arvc, char *argv[]) { return 0; }

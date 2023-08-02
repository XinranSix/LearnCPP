#include <iostream>

double const pi = 3.14159265359;

template<typename T>
struct iterator_traits;

template<typename ForwardIterator1, typename ForwardIterator2>
void iter_swap(ForwardIterator1 i1, ForwardIterator2 i2) {
    typename iterator_traits<ForwardIterator1>::value_type *pi = &*i1;
    // *i1 = *i2;
    // *i2 = tmp;
}

int main(int arvc, char *argv[]) { return 0; }

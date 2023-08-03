#include <iostream>

template<typename T>
struct List {
    template<typename T2>
    List(List<T2> const &);
};

template<typename T>
template<typename T2>
List<T>::List(List<T2> const &b) {}

template<typename T>
int length(List<T> const &);

struct Collection {
    template<typename T>
    class Node {};

    template<typename T>
    class Handle;

    template<typename T>
    T *allco() {}
};

template<typename T>
class Collection::Handle {};

int main(int arvc, char *argv[]) { return 0; }

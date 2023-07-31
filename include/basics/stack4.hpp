#include <stdexcept>

template<typename T, int MAXSIZE>
class Stack {
    T elems[MAXSIZE];
    int numElems;

public:
    void push(T const &);
    void pop();
    T top() const;
    bool empty() const { return numElems == 0; }
    bool full() const { return numElems == MAXSIZE; }
};

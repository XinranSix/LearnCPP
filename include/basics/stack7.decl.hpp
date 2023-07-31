#include <deque>
#include <memory>

template<typename T,
         template<typename ELEM, typename ALLOC = std::allocator<ELEM>>
         class CONT = std::deque>
class Stack {
private:
    CONT<T> elems;

public:
    void push(T const &);
    void pop();
    T top() const;
    bool empty() const { return elems.empty(); }
};

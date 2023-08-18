#include <iostream>

template<typename T>
struct Stack {};

template<typename T>
struct Array {};

template<typename T>
void report_top(Stack<T> const &, int number = 10);

template<typename T>
void fill(Array<T> *, T const & = T());

int main(int arvc, char *argv[]) { return 0; }

#include <iostream>
#include <memory>

template<typename T1, typename T2,
         template<typename T, typename = std::allocator<T>> class Container>
struct Relation {
private:
    Container<T1> dom1;
    Container<T2> dom2;
};

int main(int arvc, char *argv[]) { return 0; }

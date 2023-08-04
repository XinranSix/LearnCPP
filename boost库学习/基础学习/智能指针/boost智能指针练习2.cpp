#include <boost/ptr_container/ptr_vector.hpp>
#include <vector>

template<typename T>
T *create() {
    return new T;
}

int main() {

    boost::ptr_vector<int> v;
    v.push_back(create<int>());

    return 0;
}

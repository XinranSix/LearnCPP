#include <iostream>
#include <type_traits>

template<typename T>
struct RemoveReremceConst_ {
private:
    using inter_type = typename std::remove_reference<T>::type;

public:
    using type = typename std::remove_const<inter_type>::type;
};

template<typename T>
using RemoveReremceConst = typename RemoveReremceConst_<T>::type;

int main(int arvc, char *argv[]) {

    RemoveReremceConst<const int &> h = 3;

    return 0;
}

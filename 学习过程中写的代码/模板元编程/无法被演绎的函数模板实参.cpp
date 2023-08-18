#include <iostream>

template<typename DstT, typename SrcT>
inline DstT implicit_cast(SrcT const &x) {
    return x;
}

int main(int arvc, char *argv[]) {

    auto value = implicit_cast<double>(-1);

    return 0;
}

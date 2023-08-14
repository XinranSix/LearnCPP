#include <iostream>

// 酱紫做是好的
// template <typename T1, typename T2>
// decltype(auto) add(T1 const &t1, T2 const &t2) {
//     return t1 + t2;
// }

decltype(auto) add(auto const &t1, auto const &t2) {
    return t1 + t2;
}

int main(int argc, char *argv[]) {
    return 0;
}

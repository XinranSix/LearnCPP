template<typename T>
inline T const &max(T const &a, T const &b) {
    return a < b ? b : a;
}

template<typename RT, typename T1, typename T2>
inline RT max(T1 const &a, T2 const &b) {
    return a < b ? b : a;
}

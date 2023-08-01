#include <iostream>

template<typename T1, typename T2, typename T3, typename T4 = char,
         typename T5 = char>
class Quintuple; // 正确

template<typename T1, typename T2, typename T3 = char, typename T4, typename T5>
class Quintuple; // 正确，根据前面的模板声明
// T4和T5已经具有缺省值了

// template<typename T1 = char, typename T2, typename T3, typename T4, typename
// T5> class Quintuple; // 错误，T1不能具有缺省实参
// // 因为T2还没有缺省实参

int main(int arvc, char *argv[]) { return 0; }

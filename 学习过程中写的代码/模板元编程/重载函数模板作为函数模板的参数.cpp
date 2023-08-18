#include <iostream>

template<typename Func, typename T>
void apply(Func func_ptr, T x) {
    func_ptr(x);
}

template<typename T>
void single(T);

template<typename T>
void multi(T);

template<typename T>
void multi(T *);

int main(int arvc, char *argv[]) {

    apply(single<int>, 3); // 正确地
    // apply(&multi<int>, 3); // 错误地

    return 0;
}

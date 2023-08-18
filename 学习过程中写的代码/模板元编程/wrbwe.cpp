#include <iostream>
#include <functional>

template<typename X, typename UnaryOp1, typename UnaryOp2>
X apply_fg(X x, UnaryOp1 f, UnaryOp2 g) {
    return f(g(x));
}

template<typename X, typename Blob>
X apply_fg(X x, Blob blob) {
    return blob.f(blob.g(x));
}

float log2(float);

int a = apply_fg(5.0f, std::negate<float>(), log2);
int b = apply_fg(-3.14f, log2, std::negate<float>());

int main(int arvc, char *argv[]) { return 0; }

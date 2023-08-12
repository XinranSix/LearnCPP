#include <iostream>
#include <format>
#include <string>
#include <concepts>

using namespace std;

template <std::integral K, std::floating_point V>
class KeyValuePair {
public:
    KeyValuePair(K const &k, V const &v) : m_k { k }, m_v { v } {
    }

    K const &getK() const {
        return m_k;
    }
    void setK(K const &k) {
        m_k = k;
    }

    V const &getV() const {
        return m_v;
    }
    void setV(V const &v) {
        m_v = v;
    }

private:
    K m_k;
    V m_v;
};

int main(int argc, char *argv[]) {

    KeyValuePair<int, double> kv1 { 11, 2.33 };
    cout << format("{} = {}\n", kv1.getK(), kv1.getV());

    // KeyValuePair kv2{ "John Doe"s, 123456 }; //// Now causes a compilation
    // error.

    return 0;
}

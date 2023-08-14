#include <iostream>
#include <format>
#include <string>

using namespace std;

template <typename K, typename V>
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

template <typename T>
class KeyValuePair<const char *, T> {
    KeyValuePair(const char *k, T v) : m_k { k }, m_v { v } {
    }

    std::string const &getK() const {
        return m_k;
    }
    void setK(const char *k) {
        m_k = k;
    }

    T const &getV() const {
        return m_v;
    }
    void setV(T *v) {
        m_v = v;
    }

private:
    std::string m_k;
    T m_v;
};

template <typename T>
class KeyValuePair<T, const char *> {
    KeyValuePair(T k, const char *v) : m_k { k }, m_v { v } {
    }

    T const &getK() const {
        return m_k;
    }
    void setK(T k) {
        m_k = k;
    }

    std::string const &getV() const {
        return m_v;
    }
    void setV(const char *v) {
        m_v = v;
    }

private:
    T m_k;
    std::string m_v;
};

template <>
class KeyValuePair<const char *, const char *> {
public:
    KeyValuePair(const char *k, const char *v) : m_k { k }, m_v { v } {
    }

    std::string const &getK() const {
        return m_k;
    }
    void setK(const char *k) {
        m_k = k;
    }

    std::string const &getV() const {
        return m_v;
    }
    void setV(const char *v) {
        m_v = v;
    }

private:
    std::string m_k;
    std::string m_v;
};

int main(int argc, char *argv[]) {

    KeyValuePair<int, double> kv1 { 11, 2.33 };
    cout << format("{} = {}\n", kv1.getK(), kv1.getV());

    KeyValuePair kv2 { "John Doe"s, 123456 };
    cout << format("{} = {}\n", kv2.getK(), kv2.getV());


    KeyValuePair<const char *, const char *> kv3 { "John Doe", "New York" };
    cout << format("{} = {}\n", kv3.getK(), kv3.getV());

    return 0;
}

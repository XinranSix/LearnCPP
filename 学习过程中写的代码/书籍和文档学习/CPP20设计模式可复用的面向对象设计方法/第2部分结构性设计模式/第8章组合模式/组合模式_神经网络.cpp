#include <iostream>
#include <vector>

template <typename T>
concept Iterable = requires(T &t) {
    t.begin();
    t.end();
} || requires(T &t) {
    begin(t);
    end(t);
};

template <typename Self>
struct SomeNeurons {
    template <typename T>
    void connect_to(T &other);
};

template <typename T>
class Scalar : public SomeNeurons<T> {
public:
    T *begin() { return reinterpret_cast<T *>(this); }
    T *end() { return reinterpret_cast<T *>(this) + 1; }
};

struct Neuron : public Scalar<Neuron> {
    std::vector<Neuron *> in, out;
    unsigned int id;

    Neuron() {
        static int id = 1;
        this->id = id++;
    }
};

struct NeuronLayer : std::vector<Neuron> {
    NeuronLayer(int count) {
        while (count-- > 0) {
            emplace_back(Neuron {});
        }
    }
};

template <typename Self>
template <typename T>
void SomeNeurons<Self>::connect_to(T &other) {
    for (Neuron &from : *static_cast<Self *>(this)) {
        for (Neuron &to : other) {
            from.out.push_back(&to);
            to.in.push_back(&from);
        }
    }
}

template <Iterable T>
class ConnectionProxy {
    T &item;

public:
    explicit ConnectionProxy(T &item) : item { item } {}

    template <Iterable U>
    void operator>(U &other) {
        for (Neuron &from : item) {
            for (Neuron &to : other) {
                from.out.push_back(&to);
                to.in.push_back(&from);
            }
        }
    }
};

template <Iterable T>
ConnectionProxy<T> operator--(T &&item, int) {
    return ConnectionProxy<T> { item };
}

int main(int argc, char *argv[]) {

    Neuron n1, n2;
    n1-- > n2;

    return 0;
}

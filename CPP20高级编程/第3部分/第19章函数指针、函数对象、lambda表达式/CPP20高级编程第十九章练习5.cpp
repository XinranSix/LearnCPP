#include <functional>
#include <iostream>

class Processor {
public:
    Processor(std::function<int(int)> callback) : m_callback(std::move(callback)) {};

    int operator()(int value) {
        return m_callback(value);
    }

private:
    std::function<int(int)> m_callback;
};

int square(int value) {
    return value * value;
}
int cube(int value) {
    return value * value * value;
}

int main(int argc, char *argv[]) {

    Processor processor1 { square };
    std::cout << processor1(2) << std::endl;
    Processor processor2 { cube };
    std::cout << processor2(2) << std::endl;

    return 0;
}

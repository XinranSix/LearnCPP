#include <iostream>

class Base {
public:
    Base() {
    }
    ~Base() {
        std::cout << "Base 的析构函数" << std::endl;
    }
};

class Derived : public Base {
public:
    Derived() {
        m_string = new char[30];
        std::cout << "m_string allocated" << std::endl;
    };
    ~Derived() {
        delete[] m_string;
        std::cout << "m_string deallocated" << std::endl;
    }

private:
    char *m_string;
};

int main(int argc, char *argv[]) {

    Base *ptr { new Derived {} };
    delete ptr;

    return 0;
}

#include <iostream>

template <typename T>
class Pointer {
public:
    Pointer(T *ptr) : m_ptr { ptr } {}

    virtual ~Pointer() {
        delete m_ptr;
        m_ptr = nullptr;
    }

    Pointer(Pointer const &) = delete;
    Pointer<T> &operator=(Pointer const &) = delete;

public:
    T &operator*() {
        return *m_ptr;
    }

    T const &operator*() const {
        return *m_ptr;
    }

    T *operator->() {
        return m_ptr;
    }

    T const *operator->() const {
        return m_ptr;
    }

private:
    T *m_ptr { nullptr };
};

int main(int argc, char *argv[]) {

    Pointer<int> smartInt { new int };
    // *smartInt = 5;
    // std::cout << *smartInt << std::endl;

    return 0;
}

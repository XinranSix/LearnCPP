#include <iostream>

template<class T>
class Y {
private:
    Y() = default;

public:
    Y(Y &) = default;
    T &operator=(const Y &) = default;

protected:
    virtual ~Y() = default;
};

int main(int arvc, char *argv[]) { return 0; }

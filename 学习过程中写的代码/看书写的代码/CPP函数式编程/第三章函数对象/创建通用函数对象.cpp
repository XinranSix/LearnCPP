#include <iostream>
#include <utility>

class older_than {
public:
    older_than(int limit) : m_limit { limit } {}

    template <typename T>
        requires requires(T t) { std::forward<T>(t).age() > 0; }
    bool operator()(T &&object) const {
        return std::forward<T>(object).age() > m_limit;
    }

private:
    int m_limit;
};

int main(int argc, char *argv[]) {
    return 0;
}

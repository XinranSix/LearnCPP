#include <iostream>
#include <utility>

class error_test_t {
public:
    error_test_t(bool error = true) : m_error { error } {}

    template <typename T>
    bool operator()(T &&value) const {
        return m_error == static_cast<bool>(std::forward<T>(value).error());
    }

    error_test_t operator==(bool test) const {
        return error_test_t { test ? m_error : !m_error };
    }

    error_test_t operator!=(bool test) const {
        return error_test_t { !m_error };
    }

private:
    bool m_error {};
};

int main(int argc, char *argv[]) {

    error_test_t error { true };
    error_test_t not_error { false };

    return 0;
}

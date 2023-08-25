#include <iostream>
#include <mutex>
#include <utility>

// MARK: 惰性求值的一个小栗子
template <typename F>
class lazy_val {
private:
    F m_computation;
    mutable bool m_cache_initialized {};
    mutable decltype(m_computation()) m_cache {};
    mutable std::once_flag m_value_flag;

public:
    lazy_val(F computation) : m_computation { computation }, m_cache_initialized { false } {}

    operator decltype(m_computation) const &() const {
        std::call_once(m_value_flag, [this] { m_cache = m_computation(); });
        return m_cache;
    }
};

template <typename F>
inline lazy_val<F> make_lazy_val(F &&computation) {
    return lazy_val<F>(std::forward<F>(computation));
}

int main(int argc, char *argv[]) {
    return 0;
}

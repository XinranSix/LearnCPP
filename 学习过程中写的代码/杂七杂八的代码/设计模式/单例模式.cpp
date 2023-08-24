#include <iostream>
#include <memory>
#include <shared_mutex>

class SigleTon {
public:
    static SigleTon &instance() {
        static SigleTon instance;
        return instance;
    }

    SigleTon(SigleTon const &) = delete;
    SigleTon &operator=(SigleTon const &) = delete;

    SigleTon(SigleTon &&) = delete;
    SigleTon &operator=(SigleTon &&) = delete;

private:
    SigleTon() = default;
    ~SigleTon() = default;
};

int main(int argc, char *argv[]) {

    SigleTon &t = SigleTon::instance();

    return 0;
}

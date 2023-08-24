#include <iostream>
#include <memory>
#include <shared_mutex>

class SigleTon {
public:
    ~SigleTon() {
        delete single;
    }

private:
    SigleTon() {}

    static SigleTon *const single;
};

SigleTon *const SigleTon::single = new SigleTon;

class SigleTon1 {
public:
    std::shared_ptr<SigleTon1> getInstance() {
        return single;
    }

private:
    SigleTon1() {}

    static std::shared_ptr<SigleTon1> const single;
};

std::shared_ptr<SigleTon1> const SigleTon1::single { new SigleTon1 };

int main(int argc, char *argv[]) {
    return 0;
}

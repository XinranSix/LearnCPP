#include <cstddef>
#include <iostream>
#include <list>
#include <numeric>
#include <string>

class moive_t {
public:
    double average_score() const;

private:
    std::string name;
    std::list<int> scores;
    size_t scores_size;
};

double moive_t::average_score() const {
    return std::accumulate(cbegin(scores), cend(scores), 0) / static_cast<double>(scores.size());
}

int main(int argc, char *argv[]) {
    return 0;
}

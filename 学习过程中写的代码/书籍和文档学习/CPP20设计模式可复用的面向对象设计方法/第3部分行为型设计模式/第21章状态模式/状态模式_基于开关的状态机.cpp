#include <cstdio>
#include <iostream>
#include <string>

enum class State { locked, failed, unlocked };

int main(int argc, char *argv[]) {

    const std::string code { "1274" };
    auto state { State::locked };
    std::string entry;

    while (true) {
        switch (state) {
        case State::locked: {
            entry += (char)getchar();
            getchar();

            if (entry == code) {
                state = State::unlocked;
                break;
            }

            if (!code.starts_with(entry)) {
                state = State::failed;
            }
            break;
        }
        case State::failed:
            std::cout << "FAILED\n";
            return 0;
        case State::unlocked:
            std::cout << "UNLOCKED\n";
            return 0;
        }
    }

    return 0;
}

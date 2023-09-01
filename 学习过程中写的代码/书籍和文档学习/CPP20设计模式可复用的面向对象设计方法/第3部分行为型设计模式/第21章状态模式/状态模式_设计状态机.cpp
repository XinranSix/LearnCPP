#include <iostream>
#include <map>
#include <utility>
#include <vector>
#include "magic_enum.hpp"

enum class State { off_hook, connecting, connected, on_hold, on_hook };

enum class Trigger {
    call_dialed,
    hung_up,
    call_connected,
    placed_on_hold,
    taken_off_hold,
    left_message,
    stop_using_phone
};

int main(int argc, char *argv[]) {

    std::map<State, std::vector<std::pair<Trigger, State>>> rules;
    rules[State::off_hook] = { { Trigger::call_dialed, State::connecting },
                               { Trigger::stop_using_phone, State::on_hook } };
    rules[State::connecting] = { { Trigger::hung_up, State::off_hook },
                                 { Trigger::call_connected,
                                   State::connected } };

    State currentState { State::off_hook }, exitState { State::on_hook };
    while (true) {
        std::cout << "The phone is currently "
                  << magic_enum::enum_name(currentState) << std::endl;
    select_trigger:
        std::cout << "Select a trigger:\n";

        int i { 0 };
        for (auto item : rules[currentState]) {
            std::cout << i++ << ". " << magic_enum::enum_name(item.first)
                      << "\n";
        }
        int input;
        std::cin >> input;
        if (input < 0 || (input + 1) > rules[currentState].size()) {
            std::cout << "Incorrect option. Please try again.\n";
            goto select_trigger;
        }
        currentState = rules[currentState][input].second;
        if (currentState == exitState) {
            break;
        }
    }

    return 0;
}

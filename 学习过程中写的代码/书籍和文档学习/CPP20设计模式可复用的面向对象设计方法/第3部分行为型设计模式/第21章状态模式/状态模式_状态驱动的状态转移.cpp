#include <iostream>

struct State;

class LightSwitch {
    State *state { nullptr };

public:
    LightSwitch();

    void set_state(State *state);

    void on();
    void off();
};

struct State {
    virtual void on(LightSwitch *ls) { std::cout << "Light is already on\n"; }

    virtual void off(LightSwitch *ls) { std::cout << "Light is already off\n"; }
};

struct OnState : State {
    OnState() { std::cout << "Light turned on\n"; }
    void off(LightSwitch *ls) override;
};

struct OffState : State {
    OffState() { std::cout << "Light turned off\n"; }
    void on(LightSwitch *ls) override;
};

LightSwitch::LightSwitch() { state = new OffState {}; }

void LightSwitch::set_state(State *state) { this->state = state; }

void OnState::off(LightSwitch *ls) {
    std::cout << "Switching light off...\n";
    ls->set_state(new OffState {});
    delete this;
}

void LightSwitch::on() { state->on(this); }

void LightSwitch::off() { state->off(this); }

void OffState::on(LightSwitch *ls) {
    std::cout << "Switching light on...\n";
    ls->set_state(new OnState {});
    delete this;
}

int main(int argc, char *argv[]) {

    LightSwitch ls;
    ls.on();
    ls.off();
    ls.on();

    return 0;
}

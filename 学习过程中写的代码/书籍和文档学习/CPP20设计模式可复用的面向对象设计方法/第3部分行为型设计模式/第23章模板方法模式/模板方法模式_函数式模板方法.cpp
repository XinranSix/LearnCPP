#include <iostream>

struct GameState {
    int current_player, winning_player;
    int number_of_players;
};

template <typename FnStartAction, typename FnTakeTurnAction,
          typename FnHaveWinnerAction>
void run_game(GameState initial_state, FnStartAction start_action,
              FnTakeTurnAction take_turn_action,
              FnHaveWinnerAction have_winer_action) {
    GameState state = initial_state;
    start_action(state);
    while (!have_winer_action(state)) {
        take_turn_action(state);
    }
    std::cout << "Player " << state.winning_player << " wins.\n";
}

class Game {

public:
    explicit Game(int number_of_players)
        : number_of_players { number_of_players } {}

protected:
    int current_player { 0 };
    int number_of_players {};

protected:
    virtual void start() = 0;
    virtual bool have_winner() = 0;
    virtual void take_turn() = 0;
    virtual int get_winner() = 0;
};

class Chess : public Game {
public:
    explicit Chess() : Game { 2 } {}

protected:
    virtual void start() override {}

    virtual bool have_winner() override { return turns == max_turns; }

    virtual void take_turn() override {
        turns++;
        current_player = (current_player + 1) % number_of_players;
    }

    virtual int get_winner() override { return current_player; }

private:
    int turns {}, max_turns { 10 };
};

int main(int argc, char *argv[]) {

    int turn { 0 }, max_turns { 10 };
    GameState state { 0, -1, -2 };

    auto start { [](GameState &s) {
        std::cout << "Starting a game of chess with " << s.number_of_players
                  << " players\n";
    } };

    auto take_turn { [&](GameState &s) {
        std::cout << "Turn " << turn++ << " taken by player" << s.current_player
                  << "\n";
        s.current_player = (s.current_player + 1) % s.number_of_players;
        s.winning_player = s.current_player;
    } };

    auto have_winner { [&](GameState &s) { return turn == max_turns; } };

    // run_game(state, take_turn, have_winner);

    return 0;
}

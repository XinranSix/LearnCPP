#include <iostream>

class Game {

    void run() {
        start();
        while (!have_winner()) {
            take_turn();
        }
        std::cout << "Player " << get_winner() << " wins.\n";
    }

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

int main(int argc, char *argv[]) { return 0; }

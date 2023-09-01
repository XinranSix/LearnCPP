#include <format>
#include <iostream>
#include <string>
#include <utility>
#include "boost/signals2.hpp"

struct EventData {
    virtual ~EventData() = default;
    virtual void print() const = 0;
};

struct PlayerScoredData : EventData {
    std::string player_name;
    int goals_scored_so_far {};

    PlayerScoredData(std::string player_name, const int goals_scored_so_far)
        : player_name { std::move(player_name) },
          goals_scored_so_far { goals_scored_so_far } {}

    void print() const override {
        std::cout << std::format("{} has scored! (their {} goal)\n",
                                 player_name, goals_scored_so_far);
    }
};

struct Game {
    boost::signals2::signal<void(EventData *)> events;
};

struct Player {
    std::string name;
    int goals_scored {};
    Game &game;

    Player(std::string name, Game &game)
        : name { std::move(name) }, game { game } {}

    void score() {
        goals_scored++;
        PlayerScoredData ps { name, goals_scored };
        game.events(&ps);
    }
};

struct Coach {
    Game &game;

    explicit Coach(Game &game) : game { game } {
        game.events.connect([](EventData *e) {
            PlayerScoredData *ps = dynamic_cast<PlayerScoredData *>(e);
            if (ps && ps->goals_scored_so_far < 3) {
                std::cout << std::format("coach says: well done, {}\n",
                                         ps->player_name);
            }
        });
    }
};

int main(int argc, char *argv[]) {

    Game game;
    Player player { "Sam", game };
    Coach coach { game };

    player.score();
    player.score();
    player.score();

    return 0;
}

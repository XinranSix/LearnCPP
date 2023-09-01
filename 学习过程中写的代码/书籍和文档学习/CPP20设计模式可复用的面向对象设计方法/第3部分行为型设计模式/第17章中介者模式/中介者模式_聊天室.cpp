#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

struct ChatRoom;

struct Person {
    std::string name;
    ChatRoom *room { nullptr };
    std::vector<std::string> chat_log;

    Person(std::string name) : name { std::move(name) } {}

    void receive(std::string const &origin, std::string const &message);
    void say(std::string const &message) const;
    void pm(std::string const &who, std::string const &message) const;
};

struct ChatRoom {
    std::vector<Person *> people;

    void join(Person *p);
    void broadcast(std::string const &origin, std::string const &message);
    void message(std::string const &origin, std::string const &who,
                 std::string const &message);
};

void Person::receive(std::string const &origin, std::string const &message) {
    std::string s { origin + ": \"" + message + "\"" };
    std::cout << "[" << name << "'s chat session] " << s << "\n";
    chat_log.emplace_back(s);
}

void Person::say(std::string const &message) const {
    room->broadcast(name, message);
}

void Person::pm(std::string const &who, std::string const &message) const {
    room->message(name, who, message);
}

void ChatRoom::join(Person *p) {
    std::string join_msg = p->name + " joins the chat";
    broadcast("room", join_msg);
    p->room = this;
    people.push_back(p);
}

void ChatRoom::broadcast(std::string const &origin,
                         std::string const &message) {
    for (auto p : people) {
        if (p->name != origin) {
            p->receive(origin, message);
        }
    }
}

void ChatRoom::message(std::string const &origin, std::string const &who,
                       std::string const &message) {
    auto target { std::find_if(
        begin(people), end(people),
        [&](const Person *p) { return p->name == who; }) };
    if (target != end(people)) {
        (*target)->receive(origin, message);
    }
}

int main(int argc, char *argv[]) {

    ChatRoom room;

    Person john { "john" };
    Person jane { "jane" };

    room.join(&john);
    room.join(&jane);
    john.say("hi room");
    jane.say("oh, hey john");

    Person simon { "simon" };
    room.join(&simon);
    simon.say("hi everyone!");

    jane.pm("simon", "glad you could join us, simon");

    return 0;
}

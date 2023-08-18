#include <chrono>
#include <iostream>

int main(int argc, char *argv[]) {

    auto const &database { std::chrono::get_tzdb() };

    for (auto const &timezone : database.zones) {
        std::cout << timezone.name() << std::endl;
    }

    auto *brussels { std::chrono::locate_zone("Europe/Brussels") };
    auto *gmt { std::chrono::locate_zone("GMT") };
    auto *current { std::chrono::current_zone() };

    return 0;
}

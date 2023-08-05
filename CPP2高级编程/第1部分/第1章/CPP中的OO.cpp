#include <iostream>
#include <array>
#include <format>
#include <vector>
#include <compare>
#include <utility>
#include <optional>

class Airlineticket {
public:
    Airlineticket();
    ~Airlineticket(){};

    double calculatePriceInDouble();

    std::string getPassengerName();
    void setPassengerName(std::string name);

    int getNumberOfMiles();
    void setNumberOfMiles(int miles);

    bool hasEliteSuperRewardsStatus();
    void setEliteSuperRewardsStatus(bool status);

private:
    std::string m_passengerName{"Unknown Passenger"};
    bool m_hasEliteSuperRewardStatus{0};
    int m_numberOfMiles{false};
};

Airlineticket::Airlineticket() {}

double Airlineticket::calculatePriceInDouble() {
    if (hasEliteSuperRewardsStatus()) {
        return 0;
    }
    return getNumberOfMiles() * 0.1;
}

void Airlineticket::setPassengerName(std::string name) {
    m_passengerName = name;
}

std::string Airlineticket::getPassengerName() { return m_passengerName; }

int Airlineticket::getNumberOfMiles() { return m_numberOfMiles; }

void Airlineticket::setNumberOfMiles(int miles) { m_numberOfMiles = miles; }

bool Airlineticket::hasEliteSuperRewardsStatus() {
    return m_hasEliteSuperRewardStatus;
}

void Airlineticket::setEliteSuperRewardsStatus(bool status) {
    m_hasEliteSuperRewardStatus = status;
}

int main(int arvc, char *argv[]) {

    Airlineticket myTicket;

    myTicket.setPassengerName("Sherman T. Socketwrench");
    myTicket.setNumberOfMiles(700);
    double cont{myTicket.calculatePriceInDouble()};

    std::cout << std::format("This ticket will cost ${}", cont) << std::endl;

    return 0;
}

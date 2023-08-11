#include <iostream>
#include <array>
#include <format>
#include <vector>
#include <compare>
#include <utility>
#include <optional>

class AirlineTicket {
public:
    AirlineTicket();
    ~AirlineTicket(){};

    double calculatePriceInDollars() const;

    std::string getPassengerName() const;
    void setPassengerName(std::string const &name);

    int getNumberOfMiles() const;
    void setNumberOfMiles(int miles);

    bool hasEliteSuperRewardsStatus() const;
    void setEliteSuperRewardsStatus(bool status);

private:
    std::string m_passengerName{"Unknown Passenger"};
    bool m_hasEliteSuperRewardStatus{0};
    int m_numberOfMiles{false};
};

AirlineTicket::AirlineTicket() {}

double AirlineTicket::calculatePriceInDollars() const {
    if (hasEliteSuperRewardsStatus()) {
        return 0;
    }
    return getNumberOfMiles() * 0.1;
}

void AirlineTicket::setPassengerName(std::string const &name) {
    m_passengerName = name;
}

std::string AirlineTicket::getPassengerName() const { return m_passengerName; }

int AirlineTicket::getNumberOfMiles() const { return m_numberOfMiles; }

void AirlineTicket::setNumberOfMiles(int miles) { m_numberOfMiles = miles; }

bool AirlineTicket::hasEliteSuperRewardsStatus() const {
    return m_hasEliteSuperRewardStatus;
}

void AirlineTicket::setEliteSuperRewardsStatus(bool status) {
    m_hasEliteSuperRewardStatus = status;
}

int main(int arvc, char *argv[]) {

    AirlineTicket myTicket;

    myTicket.setPassengerName("Sherman T. Socketwrench");
    myTicket.setNumberOfMiles(700);
    double cont{myTicket.calculatePriceInDollars()};

    std::cout << std::format("This ticket will cost ${}", cont) << std::endl;

    return 0;
}

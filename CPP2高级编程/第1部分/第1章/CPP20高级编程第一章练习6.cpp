#include <iostream>
#include <array>
#include <format>
#include <vector>
#include <compare>
#include <utility>
#include <optional>

enum class Number {};

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

    std::optional<int> getFrequentFlyerNumber() const;
    void setFrequentFlyerNumber(int number);

private:
    std::string m_passengerName{"Unknown Passenger"};
    bool m_hasEliteSuperRewardStatus{0};
    int m_numberOfMiles{false};
    std::optional<int> m_frequentFlyerNumber;
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

std::optional<int> AirlineTicket::getFrequentFlyerNumber() const {
    return m_frequentFlyerNumber;
}

void AirlineTicket::setFrequentFlyerNumber(int number) {
    m_frequentFlyerNumber = number;
}

int main() {
    AirlineTicket myTicket; // Stack-based AirlineTicket
    myTicket.setPassengerName("Sherman T. Socketwrench");
    myTicket.setNumberOfMiles(700);
    myTicket.setFrequentFlyerNumber(123'456);
    const double cost{myTicket.calculatePriceInDollars()};
    std::cout << std::format("This ticket will cost ${}", cost) << std::endl;

    const auto frequentFlyerNumber{myTicket.getFrequentFlyerNumber()};
    if (frequentFlyerNumber) {
        std::cout << std::format("Frequent flyer number: {}",
                                 frequentFlyerNumber.value())
                  << std::endl;
    } else {
        std::cout << "No frequent flyer number." << std::endl;
    }
}

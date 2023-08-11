#include <iostream>
#include <string>

void mysteryFunction(const std::string *something) {
    // *something = "Test";
}

void func(const int param) {}

class AirlineTicket {
public:
    AirlineTicket();
    ~AirlineTicket(){};

    double calculatePriceInDollars() const;

    std::string getPassengerName() const;
    void setPassengerName(std::string name);

    int getNumberOfMiles() const;
    void setNumberOfMiles(int miles);

    bool hasEliteSuperRewardsStatus() const;
    void setEliteSuperRewardsStatus(bool status);

private:
    std::string m_passengerName{"Unknown Passenger"};
    bool m_hasEliteSuperRewardStatus{0};
    int m_numberOfMiles{false};
};

int main(int arvc, char *argv[]) {

    // 修饰类型
    const int versionNumberMajor{2};
    const int versionNumberMinor{3};
    const std::string productName{"Super Hyper Net Modulator"};
    const double PI{3.14159263589793238462};

    // 修饰指针
    int const *const ip{new int[10]};
    // ip =
    // ip[4] = 5;

    std::string myString{"The string"};
    mysteryFunction(&myString);

    return 0;
}

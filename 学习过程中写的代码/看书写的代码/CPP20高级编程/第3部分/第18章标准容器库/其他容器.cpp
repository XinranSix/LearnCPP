#include <bitset>
#include <stdexcept>
#include <string>
#include <iostream>
#include <gtest/gtest.h>
#include <string_view>

TEST(其他容器, 标准C风格数组) {
    const size_t count { 10 };
    int values[count];

    for (int i { 0 }; i < count; ++i) {
        values[i] = i;
    }

    std::vector<int> vec;
    // vec.insert(end(vec), values, values + count);
    vec.insert(end(vec), std::cbegin(values), std::cend(values));

    for (auto const &i : vec) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

TEST(其他容器, string) {
    std::string myString;
    myString.insert(cend(myString), 'h');
    myString.insert(cend(myString), 'e');
    myString.push_back('l');
    myString.push_back('l');
    myString.push_back('o');

    for (auto const &letter : myString) {
        std::cout << letter;
    }
    std::cout << std::endl;

    for (auto it { cbegin(myString) }; it != cend(myString); ++it) {
        std::cout << *it;
    }
    std::cout << std::endl;
}

TEST(其他容器, bitset基础) {
    std::bitset<10> myBitset;

    myBitset.set(3);
    myBitset.set(6);
    myBitset[8] = true;
    myBitset[9] = myBitset[3];

    if (myBitset.test(3)) {
        std::cout << "Bit 3 is set!" << std::endl;
    }
    std::cout << myBitset << std::endl;
}

TEST(其他容器, bitset按位运算符) {
    auto str1 { "0011001100" };
    auto str2 { "0000111100" };

    std::bitset<10> bitsOne { str1 };
    std::bitset<10> bitsTwo { str2 };

    auto bitsThree { bitsOne & bitsTwo };
    std::cout << bitsThree << std::endl;
    bitsThree <<= 4;
    std::cout << bitsThree << std::endl;
}

class CableCompany final {
public:
    static const size_t NumChannels { 10 };

    void addPackage(std::string_view packageName, std::bitset<NumChannels> const &channels);

    void addPackage(std::string_view packageName, std::string_view channels);

    void removePackage(std::string_view packageName);

    std::bitset<NumChannels> const &getPackage(std::string_view packageName) const;

    void newCustomer(std::string_view name, std::string_view package);

    void newCustomer(std::string_view name, std::bitset<NumChannels> const &channels);

    void addChannel(std::string_view name, int channel);

    void removeChannel(std::string_view name, int channel);

    void addPackageToCustomer(std::string_view name, std::string_view package);

    void deleteCustomer(std::string_view name);

    std::bitset<NumChannels> &getCustomerChannels(std::string_view name) const;

private:
    std::bitset<NumChannels> &getCustomerChannelsHelper(std::string_view name);

    using MapType = std::map<std::string, std::bitset<NumChannels>>;
    MapType m_packages, m_customers;
};

void CableCompany::addPackage(std::string_view packageName,
                              std::bitset<NumChannels> const &channels) {
    m_packages.emplace(packageName, channels);
}

void CableCompany::addPackage(std::string_view packageName, std::string_view channels) {
    addPackage(packageName, std::bitset<NumChannels> { channels.data() });
}

void CableCompany::removePackage(std::string_view packageName) {
    m_packages.erase(packageName.data());
}

std::bitset<CableCompany::NumChannels> const &
CableCompany::getPackage(std::string_view packageName) const {
    if (auto it { m_packages.find(packageName.data()) }; it != end(m_packages)) {
        return it->second;
    }
    throw std::out_of_range { "Invaild package" };
}

void CableCompany::newCustomer(std::string_view name, std::string_view package) {
    auto &packageChannels { getPackage(package) };
    newCustomer(name, packageChannels);
}

void CableCompany::newCustomer(std::string_view name, std::bitset<NumChannels> const &channels) {
    if (auto [iter, success] { m_customers.emplace(name, channels) }; !success) {
        throw std::invalid_argument { "Duplicate customer" };
    }
}

void CableCompany::addChannel(std::string_view name, int channel) {
    auto &customerChannels { getCustomerChannelsHelper(name) };
    customerChannels.set(channel);
}

void CableCompany::removeChannel(std::string_view name, int channel) {
    auto &customerChannels { getCustomerChannelsHelper(name) };
    customerChannels.reset(channel);
}

void CableCompany::addPackageToCustomer(std::string_view name, std::string_view package) {
    auto &packageChannels { getPackage(package) };
    auto &customerChannels { getCustomerChannelsHelper(name) };
    customerChannels |= packageChannels;
}

void CableCompany::deleteCustomer(std::string_view name) {
    m_customers.erase(name.data());
}

std::bitset<CableCompany::NumChannels> &
CableCompany::getCustomerChannels(std::string_view name) const {
    return const_cast<std::bitset<NumChannels> &>(std::as_const(*this).getCustomerChannels(name));
}

std::bitset<CableCompany::NumChannels> &
CableCompany::getCustomerChannelsHelper(std::string_view name) {
    if (auto it { m_customers.find(name.data()) }; it != end(m_customers)) {
        return it->second;
    }
    throw std::invalid_argument { "Unknown customer" };
}

TEST(其他容器, bitset示例_表示有线电视频道) {
    CableCompany myCC;
    myCC.addPackage("basic", "1111000000");
    myCC.addPackage("premium", "1111111111");
    myCC.addPackage("sports", "0000100111");

    myCC.newCustomer("Marc G.", "basic");
    myCC.addPackageToCustomer("Marc G.", "sports");
    std::cout << myCC.getCustomerChannels("Marc G.") << std::endl;
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

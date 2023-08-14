#include <bitset>
#include <ios>
#include <iostream>
#include <format>
#include <cstddef>
#include <limits>
#include <cmath>

namespace mycode {
    void foo() {
        std::cout << "foo() called in the mycode namespace" << std::endl;
    }
}; // namespace mycode

namespace MyLibraries::Networking::FTP {}

namespace MyLibraries {
    namespace Networking {
        namespace FTP {}
    } // namespace Networking
} // namespace MyLibraries

namespace MyFTP = MyLibraries::Networking::FTP;

int main(int arvc, char *argv[]) {

    std::cout << "Hello World!" << std::endl;
    std::cout << "There are " << 219 << " ways I love you." << std::endl;
    std::cout << std::format("There are {} ways I love you.", 219) << std::endl;

    // int value{};
    // std::cin >> value;
    // std::cout << value << '\n';

    mycode::foo();

    std::cout << 123 << '\n';
    std::cout << std::oct << 0173 << '\n';
    std::cout << std::hex << 0x7b << std::dec << '\n';
    std::cout << std::bitset<32>(0b1111011) << '\n';

    std::cout << 3.14f << '\n';
    std::cout << 3.14 << '\n';
    std::cout << 0x3.ABCp-10 << '\n';
    std::cout << 0Xb.cp121 << '\n';
    std::cout << 'a' << '\n';
    std::cout << 23'456'789 << '\n';
    std::cout << 0.123'456f << '\n';

    int uninitializedInt;
    int initializedInt{7};
    std::cout << std::format("{} is a random value", uninitializedInt)
              << std::endl;
    std::cout << std::format("{} was assigned an initial value", initializedInt)
              << std::endl;

    int i1{-7};
    signed int i2{-6};
    signed i3{-5};

    short s1{13};
    short int s2{14};
    signed short s3{15};
    signed short int s4{16};

    long l{7L};

    long long ll{14LL};

    unsigned int i{2U};
    unsigned j{5U};
    unsigned short s{23U};
    unsigned long l1{5400UL};
    unsigned long long ll1{140ULL};

    float ch{7.2f};
    double d1{7.2};
    long double d2{16.98L};

    char ch1{'m'};

    char8_t c8{u8'm'};
    char16_t c16{u'm'};
    char32_t c32{U'm'};

    wchar_t w{L'm'};
    bool b{true};

    std::byte b1{42};

    std::cout << "int:\n";
    std::cout << std::format("Max int value: {}\n",
                             std::numeric_limits<int>::max());
    std::cout << std::format("Min int value: {}\n",
                             std::numeric_limits<int>::min());
    std::cout << std::format("Lowest int value: {}\n",
                             std::numeric_limits<int>::lowest());

    std::cout << "\ndouble:\n";
    std::cout << std::format("Max double value: {}\n",
                             std::numeric_limits<double>::max());
    std::cout << std::format("Min double value: {}\n",
                             std::numeric_limits<double>::min());
    std::cout << std::format("Lowest double value: {}\n",
                             std::numeric_limits<double>::lowest());

    // 零初始化
    float myFloat{};
    int myInt{};

    float myFloat1{3.14f};
    int i4{(int)myFloat1};
    int i5{int(myFloat1)};
    int i6{static_cast<int>(myFloat1)};

    std::cout << std::numeric_limits<double>::infinity() << std::endl;
    std::cout << std::isinf(std::numeric_limits<double>::infinity())
              << std::endl;
    std::cout << std::isnan(std::numeric_limits<double>::quiet_NaN())
              << std::endl;

    return 0;
}

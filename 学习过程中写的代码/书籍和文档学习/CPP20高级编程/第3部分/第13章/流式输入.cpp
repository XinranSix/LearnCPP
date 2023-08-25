#include <cctype>
#include <cstdlib>
#include <format>
#include <iostream>
#include <gtest/gtest.h>
#include <istream>
#include <string>

void getReservationData() {
    std::string guestName;
    int partySize {};
    std::cout << "Name and number of guests: ";
    std::cin >> guestName >> partySize;
    std::cout << "Thank you, " << guestName << "." << std::endl;
    if (partySize > 10) {
        std::cout << "An extra gratuity will apply." << std::endl;
    }
}

TEST(流式输入, 基本输入) {
    std::string userInput;
    std::cin >> userInput;
    std::cout << "User input was " << userInput << std::endl;

    int userInput1 {};
    std::cin >> userInput1;
    std::cout << "User input was " << userInput1 << std::endl;
}

TEST(流式输入, 处理错误输出) {

    std::cout << "Enter numbers on separate lines to add."
              << "Use Control+D to followed by Enter to finish (Control+Z in "
                 "Windowns).\n";
    int sum { 0 };

    if (!std::cin.good()) {
        std::cerr << "Standard input is a bad state!" << std::endl;
        exit(1);
    }

    while (!std::cin.bad()) {
        int number;
        std::cin >> number;
        if (std::cin.good()) {
            sum += number;
        } else if (std::cin.fail()) {
            std::cin.clear();
            std::string badToken;
            std::cin >> badToken;
            std::cerr << "WARNING: Bad input encountered: " << badToken
                      << std::endl;
        }
    }
    std::cout << "The sum is " << sum << std::endl;
}

std::string readName(std::istream &stream) {
    std::string name;
    while (stream) {
        int next = stream.get();
        if (!stream || next == std::char_traits<char>::eof()) {
            break;
        }
        name += static_cast<char>(next);
    }
    return name;
}

std::string readName1(std::istream &stream) {
    std::string name;
    char next;
    while (stream.get(next)) {
        name += next;
    }
    return name;
}

TEST(流式输入, 输入方法) {
}

void getReservationData1() {
    std::string guestName;
    int partySize { 0 };
    char ch;
    std::cin >> std::noskipws;
    while (std::cin >> ch) {
        if (std::isdigit(ch)) {
            std::cin.unget();
            if (std::cin.fail()) {
                std::cout << "unget() failed" << std::endl;
            }
            break;
        }
        guestName += ch;
    }

    if (std::cin) {
        std::cin >> partySize;
    }

    if (!std::cin) {
        std::cerr << "Error getting party size." << std::endl;
        return;
    }

    std::cout << std::format("Thank you '{}', party of {}", guestName,
                             partySize)
              << std::endl;
    if (partySize > 10) {
        std::cout << "An extra gratuity will apply." << std::endl;
    }
}

TEST(流式输入, unget) {
}

TEST(流式输入, putback) {
    char c;
    std::cin >> c;
    std::cout << std::format("Retrieved {} before putback('e')", c)
              << std::endl;

    std::cin.putback('e');
    std::cin >> c;
    std::cout << std::format("Retireved{} after putback('e')", c) << std::endl;
}

void getReservationData2() {
    std::string guestName;
    int partySize { 0 };
    char ch;
    std::cin >> std::noskipws;
    while (true) {
        ch = static_cast<char>(std::cin.peek());
        if (!std::cin) {
            break;
        }
        if (isdigit(ch)) {
            break;
        }
        std::cin >> ch;
        if (!ch) {
            break;
        }
        guestName += ch;
    }
    if (std::cin) {
        std::cin >> partySize;
    }
    if (!std::cin) {
        std::cerr << "Error getting party size." << std::endl;
        return;
    }

    std::cout << std::format("Thank you '{}', party of {}", guestName,
                             partySize)
              << std::endl;
    if (partySize > 10) {
        std::cout << "An extra gratuity will apple." << std::endl;
    }
}

TEST(流式输入, peek) {
}

TEST(流式输入, getline) {
    constexpr size_t kBufferSize { 1024 };
    char buffer[kBufferSize] { 0 };
    std::cin.getline(buffer, kBufferSize);

    std::string myString;
    std::getline(std::cin, myString);

    std::getline(std::cin, myString, '@');
}

TEST(流式输入, 输入操作算子) {
    
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

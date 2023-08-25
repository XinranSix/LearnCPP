#include <format>
#include <iostream>
#include <gtest/gtest.h>
#include <regex>
#include <string>

TEST(正则表达式, regex_match示例) {
#if 0
    std::regex r { "(\\d{4})/(0?[1-9]|1[0-2])/(0?[1-9]|[1-2][0-9]|3[0-1])" };
    std::string str;

    while (true) {
        std::cout << "Enter a data (year/month/day) (q=quit): ";
        std::string str;
        if (!std::getline(std::cin, str) || str == "q") {
            break;
        }

        if (std::smatch m; std::regex_match(str, m, r)) {
            int year { stoi(m[1]) };
            int month { stoi(m[2]) };
            int day { stoi(m[3]) };
            std::cout << std::format(" Valid data: Year={}, month={}, day={}", year, month, day)
                      << std::endl;
        } else {
            std::cout << " Invalid data!" << std::endl;
        }
    }
#endif
}

TEST(正则表达式, regex_search示例) {
#if 0
    std::regex r { "//\\s*(.+)$" };
    while (true) {
        std::cout << "Enter a string with opertion code comments (q=quit): ";
        std::string str;
        if (!std::getline(std::cin, str) || str == "q") {
            break;
        }

        if (std::smatch m; std::regex_search(str, m, r)) {
            std::cout << std::format(" Found comment '{}'", m[1].str()) << std::endl;
        } else {
            std::cout << " No comment found!" << std::endl;
        }
    }
#endif
}

TEST(正则表达式, regex_iterator示例) {
#if 0
    std::regex reg { "[\\w]+" };
    while (true) {
        std::cout << "Enter a string a to split (q=quit): ";
        std::string str;
        if (!std::getline(std::cin, str) || str == "q") {
            break;
        }

        const std::sregex_iterator end;
        for (std::sregex_iterator iter { cbegin(str), cend(str), reg }; iter != end; ++iter) {
            std::cout << std::format("\"{}\"", (*iter)[0].str()) << std::endl;
        }
    }
#endif
}

TEST(正则表达式, regex_token_iterator示例) {
#if 1

#endif
}

TEST(正则表达式, regex_token_replace示例) {
#if 1

#endif
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

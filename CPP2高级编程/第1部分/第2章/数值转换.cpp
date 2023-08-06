#include <iostream>
#include <string>
#include <format>
#include <charconv>
#include <cstddef>
#include <gtest/gtest.h>

TEST(数值转换, 高级数值转换函数) {
    // 高级数值转换函数
    long double d{3.14L};
    std::string s{std::to_string(d)};

    const std::string toParse{"   123USD"};
    size_t index{0};
    int value{stoi(toParse, &index)};
    std::cout << std::format("Parsed Value: {}", value) << std::endl;
    std::cout << std::format("First non-parsed character: {}", toParse[index])
              << std::endl;
}

TEST(数值转换, 低级数值转换函数) {
    // 低级数值转换函数
    const size_t BufferSize{50};

    {
        std::string out{BufferSize, ' '};
        auto result{std::to_chars(out.data(), out.data() + out.size(), 12345)};
        if (result.ec == std::errc{}) {
            std::cout << out << std::endl;
        }
    }

    {
        std::string out(BufferSize, ' ');
        auto result{std::to_chars(out.data(), out.data() + out.size(), 12345)};
        if (result.ec == std::errc{}) {
            std::cout << out << std::endl;
        }
    }

    {
        std::string out1{BufferSize, '='};
        std::string out2(BufferSize, '-');
        std::cout << out1 << std::endl << out2 << std::endl;
    }

    {
        double value{0.314};
        std::string out(BufferSize, ' ');
        auto [ptr,
              error]{std::to_chars(out.data(), out.data() + out.size(), value)};
        if (error == std::errc()) {
            std::cout << out << std::endl;
        }
    }

    {
        double value1{0.314};
        std::string out(BufferSize, ' ');
        auto [ptr1, error1]{
            std::to_chars(out.data(), out.data() + out.size(), value1)};
        if (error1 == std::errc{}) {
            std::cout << out << std::endl;
        }

        double value2;
        auto [ptr2, error2]{
            std::from_chars(out.data(), out.data() + out.size(), value2)};
        if (error2 == std::errc{}) {
            if (value1 == value2) {
                std::cout << "Prefect roundtrip" << std::endl;
            } else {
                std::cout << "No Prefect roundtrip?!?" << std::endl;
            }
        }
    }
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

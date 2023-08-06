#include <iostream>
#include <gtest/gtest.h>
#include <string_view>
#include <format>

std::string_view extractExtension(std::string_view filename) {
    return filename.substr(filename.rfind('.'));
}

TEST(STRING_VIEW, extractExtension) {
    std::string filename{R"(c:\temp\my file.ext)"};
    std::cout << std::format("C++ string: {}", extractExtension(filename))
              << std::endl;

    const char *cString{R"(c:\temp\my file.ext)"};
    std::cout << std::format("C string: {}", extractExtension(cString))
              << std::endl;

    std::cout << std::format("Literal: {}",
                             extractExtension(R"(c:\temp\my file.ext)"))
              << std::endl;
}

void handleExtension(const std::string &extension) {}

TEST(STRING_VIEW, 从原始缓冲区和长度构造) {
    const char *raw{R"(c:\temp\my file.ext)"};
    size_t length{19};
    std::cout << std::format("Raw: {}", extractExtension({raw, length}))
              << std::endl;
    std::cout << std::format("Raw: {}",
                             extractExtension(std::string_view{raw, length}))
              << std::endl;
}

TEST(STRING_VIEW, 从string_view构造string) {
    // handleExtension(extractExtension("my file.ext"));
    handleExtension(extractExtension("my file.ext").data());
    handleExtension(std::string{extractExtension("my file.ext")});
}

TEST(STRING_VIEW, 无法连接string和string_view) {
    std::string str{"Hello"};
    std::string_view sv{" world"};
    // auto result{str + sv}; // Error

    auto result1{str + sv.data()};

    auto result2{str};
    result2.append(sv.data(), sv.size());
}

TEST(STRING_VIEW, string_view不应该保存一个临时字符串的试图) {

    std::string s{"Hello"};
    std::string_view sv{s + " World!"};
    std::cout << sv << std::endl;
}

TEST(STRING_VIEW, string_view字面量) {

    using namespace std;

    auto sv{"My string_sv"sv};
    std::cout << sv << std::endl;
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

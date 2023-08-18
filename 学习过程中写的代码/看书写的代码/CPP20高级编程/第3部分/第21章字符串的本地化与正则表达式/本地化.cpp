#include <format>
#include <iostream>
#include <gtest/gtest.h>
#include <locale>
#include <string>

// 做的超级烂

TEST(本地化, 宽字符) {
    wchar_t myWideCharacter { L'm' };

    std::wcout << L"I am a wide-character string literal." << std::endl;
}

TEST(本地化, 非西方字符集) {
    const char8_t *s1 { u8R"(Raw UTF-8 encoded string literal)" };
    const wchar_t *s2 { LR"(Raw wide string literal)" };
    const char16_t *s3 { uR"(Raw char16_t strign literal)" };
    const char32_t *s4 { UR"(Raw char32_t string literal)" };

    const char8_t *formula { u8"03C0 r\u00B2" };

    auto str = std::u8string { formula };
}

TEST(本地化, 使用locale) {
    // std::wcout.imbue(std::locale { "en-US" });
    // std::wcout << 32767 << std::endl;
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

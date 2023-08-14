#include <iostream>
#include <filesystem>

int main(int argc, char *argv[]) {

    std::filesystem::path p1 { R"(D:\Foo\Bar)" };
    std::filesystem::path p2 { R"(D:/Foo/Bar)" };
    std::filesystem::path p3 { R"(D:/Foo/Bar/MyFile.txt)" };
    std::filesystem::path p4 { R"(..\SomeFolder)" };
    std::filesystem::path p5 { R"(/usr/lib/X11)" };

    std::cout << p1 << std::endl;
    std::cout << p2 << std::endl;
    std::cout << p3 << std::endl;
    std::cout << p4 << std::endl;
    std::cout << p5 << std::endl;

    std::filesystem::path p { "D:\\Foo" };
    p.append("Bar");
    p /= "Bar";
    std::cout << p << std::endl;

    std::filesystem::path p6 { "D:\\Foo" };
    p6.concat("Bar");
    p6 += "Bar";
    std::cout << p6 << std::endl;

    std::filesystem::path p7 { R"(/Foo/Bar)" };
    for (auto const &compoent : p7) {
        std::cout << compoent << std::endl;
    }

    return 0;
}

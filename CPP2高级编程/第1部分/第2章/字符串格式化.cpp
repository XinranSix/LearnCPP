#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include <format>

TEST(字符串格式化, format) {
    int n{1};
    auto s1{std::format(R"(Read {} bytes from {})", n, "file1.txt")};
    // auto s2{std::format("Read {0} bytes from {}", n, "file1.txt")}; // Error
    auto s2{std::format("Read {0} bytes from {1}", n, "file1.txt")};
    auto s3{std::format(L"从 {1} 中读取 {0} 个字节", n, L"file1.txt")};

    std::cout << s1 << std::endl;
    std::cout << s2 << std::endl;
    std::wcout << s3 << std::endl;
}

TEST(字符串格式化, 格式说明符) {
    int i{42};
    std::cout << std::format("|{:5}|", i) << std::endl;
    std::cout << std::format("|{:{}}|", i, 7) << std::endl;

    int j{42};
    std::cout << std::format("|{:7}|", j) << std::endl;
    std::cout << std::format("|{:<7}|", j) << std::endl;
    std::cout << std::format("|{:_>7}|", j) << std::endl;
    std::cout << std::format("|{:_^7}|", j) << std::endl;
    std::cout << std::format("|{:_<7}|", j) << std::endl;

    int k{42};
    std::cout << std::format("|{:<5}|", i) << std::endl;
    std::cout << std::format("|{:<+5}|", i) << std::endl;
    std::cout << std::format("|{:< 5}|", i) << std::endl;
    std::cout << std::format("|{:< 5}|", -i) << std::endl;
}

TEST(字符串格式化, 格式说明符之备用格式) {

    int i{42};
    std::cout << std::format("|{:10d}|", i) << std::endl;
    std::cout << std::format("|{:10b}|", i) << std::endl;
    std::cout << std::format("|{:#10b}|", i) << std::endl;
    std::cout << std::format("|{:10X}|", i) << std::endl;
    std::cout << std::format("|{:#10X}|", i) << std::endl;

    std::string s{"ProCpp"};
    std::cout << std::format("|{:_^10}|", s) << std::endl;

    double d{3.1415 / 2.3};
    std::cout << std::format("|{:12g}|", d) << std::endl;
    std::cout << std::format("|{:12.2}|", d) << std::endl;
    std::cout << std::format("|{:12e}|", d) << std::endl;

    int width{12};
    int precision{3};
    std::cout << std::format("|{2:{0}.{1}f}|", width, precision, d)
              << std::endl;
}

TEST(字符串格式化, 0) {

    int i{42};
    std::cout << std::format("|{:06d}|", i) << std::endl;
    std::cout << std::format("|{:+06d}|", i) << std::endl;
    std::cout << std::format("|{:06x}|", i) << std::endl;
    std::cout << std::format("|{:#06x}|", i) << std::endl;
}

TEST(字符串格式化, 格式说明符错误) {

    try {
        // std::cout << std::format("An integer: {:.}", 5) << std::endl;
    } catch (const std::format_error &e) {
        std::cout << e.what() << std::endl;
    }
}

struct KeyValue {
    KeyValue(std::string_view key, int value) : m_key{key}, m_value{value} {}

    std::string const &getKey() const { return m_key; }
    int getValue() const { return m_value; }

private:
    std::string m_key;
    int m_value;
};

template<>
class std::formatter<KeyValue> {
public:
    constexpr auto parse(auto &context) {

        auto iter{context.begin()};
        const auto end{context.end()};
        if (iter == end || *iter == '}') {
            m_outputType = OutputType::KeyAndValue;
            return iter;
        }

        switch (*iter) {
        case 'a':
            m_outputType = OutputType::KeyOnly;
            break;
        case 'b':
            m_outputType = OutputType::ValueOnly;
            break;
        case 'c':
            m_outputType = OutputType::KeyAndValue;
            break;
        default:
            throw std::format_error{"Invalid KeyValue format specifier."};
        }

        ++iter;
        if (iter != end && *iter != '}') {
            throw std::format_error{"Invalid KeyValue format specifier."};
        }
        return iter;
    }

    auto format(KeyValue const &kv, auto &context) {
        switch (m_outputType) {
            using enum OutputType;
        case KeyOnly:
            return format_to(context.out(), "{}", kv.getKey());
        case ValueOnly:
            return format_to(context.out(), "{}", kv.getValue());
        default:
            return format_to(context.out(), "{} - {}", kv.getKey(),
                             kv.getValue());
        }
    }

private:
    enum class OutputType { KeyOnly, ValueOnly, KeyAndValue };

    OutputType m_outputType{OutputType::KeyAndValue};
};

TEST(字符串格式化, 支持自定义类型) {
    KeyValue keyValue{"Key1", 11};
    std::cout << std::format("{}", keyValue) << std::endl;
    std::cout << std::format("{:a}", keyValue) << std::endl;
    std::cout << std::format("{:b}", keyValue) << std::endl;
    std::cout << std::format("{:c}", keyValue) << std::endl;
    try {
        // std::cout << std::format("{:cd}", keyValue) << std::endl;
    } catch (const std::format_error &e) {
        std::cout << e.what();
    }
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

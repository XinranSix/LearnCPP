#include <cstddef>
#include <format>
#include <iostream>
#include <gtest/gtest.h>
#include <functional>
#include <unordered_map>
#include <unordered_set>
#include <utility>

class IntWrapper {
public:
    IntWrapper(int i) : m_wrappedInt { i } {}

    int getValue() const {
        return m_wrappedInt;
    }

    bool operator==(IntWrapper const &) const = default;

private:
    int m_wrappedInt;
};

namespace std {
    template <>
    struct hash<IntWrapper> {
        size_t operator()(IntWrapper const &x) const {
            return std::hash<int> {}(x.getValue());
        }
    };
} // namespace std

TEST(无序相关容器, 哈希函数) {}

TEST(无序相关容器, unordered_map) {
    std::unordered_map<int, std::string> m {
        { 1, "Item 1" }, { 2, "Item 2" }, { 3, "Item 3" }, { 4, "Item 4" }
    };

    for (auto const &[k, v] : m) {
        std::cout << std::format("{} = {}", k, v) << std::endl;
    }

    for (auto const &p : m) {
        std::cout << std::format("{} = {}", p.first, p.second) << std::endl;
    }
}

/* -------------------------------------------------------------------------- */

void printMap(auto const &m) {
    for (auto &[k, v] : m) {
        std::cout << std::format("{} (Phone: {})", k, v) << std::endl;
    }
    std::cout << "-------" << std::endl;
}

TEST(无序相关容器, unordered_map示例_电话簿) {
    std::unordered_map<std::string, std::string> phoneBook { { "Marc G.", "123-456789" },
                                                             { "Scott K.", "645-987321" } };

    printMap(phoneBook);

    phoneBook.insert(std::make_pair("John D.", "321-987654"));
    phoneBook["Johan G."] = "963-258147";
    phoneBook["Freddy K."] = "999-256256";
    phoneBook.erase("Freddy K.");
    printMap(phoneBook);

    const size_t bucket { phoneBook.bucket("Marc G.") };
    std::cout << std::format("Marc G. is in bucket {} containing the following {} names:", bucket,
                             phoneBook.bucket_size(bucket))
              << std::endl;
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

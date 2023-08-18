#include <iostream>
#include <format>
#include <string>
#include <string_view>
#include <vector>
#include <unordered_map>

template <typename T>
class AssociativeArray {
public:
    virtual ~AssociativeArray() = default;

    T &operator[](std::string_view key);
    T const &operator[](std::string_view key) const;

private:
    struct Element {
        Element(std::string key, T value)
            : m_key { std::move(key) }, m_value { std::move(value) } {}

        std::string m_key;
        T m_value;
    };
    std::vector<Element> m_data;
};

template <typename T>
T &AssociativeArray<T>::operator[](std::string_view key) {
    for (auto &element : m_data) {
        if (element.m_key == key) {
            return element.m_value;
        }
    }

    m_data.push_back(Element { std::string { key }, T {} });
    return m_data.back().m_value;
}

template <typename T>
T const &AssociativeArray<T>::operator[](std::string_view key) const {
    for (auto &element : m_data) {
        if (element.m_key == key) {
            return element.m_value;
        }
    }
    throw std::invalid_argument { std::format("Key '{}' doesn't exist.", key.data()) };
}

int main(int argc, char *argv[]) {

    std::unordered_map<std::string, int> myArray;
    myArray["Key 1"] = 11;
    myArray["Key 2"] = 22;
    myArray["Key 3"] = 33;

    std::cout << myArray["Key 1"] << std::endl;
    std::cout << myArray["Key 2"] << std::endl;

    //// std::unordered_map does not support operator[]
    //// on const instances.
    // Test const operator[]
    // const AssociativeArray<int>& c{ myArray };
    // cout << c["Key 3"] << endl;
    // cout << c["Key 4"] << endl;

    //// Instead, you can use find().
    const auto &c { myArray };
    std::cout << c.find("Key 3")->second << std::endl;
    auto res { c.find("Key 4") };
    if (res == end(c)) {
        std::cout << "Key 4 not found." << std::endl;
    }
    return 0;
}

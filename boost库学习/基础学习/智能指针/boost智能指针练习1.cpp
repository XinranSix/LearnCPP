#include <boost/shared_array.hpp>
#include <cstring>
#include <iostream>

boost::shared_array<char> get(const boost::shared_array<char> s) {
    int size = std::strlen(s.get());
    char *text = new char[size + 1];
    std::strncpy(text, s.get(), size + 1);
    return boost::shared_array<char>{text};
}

void print(boost::shared_array<char> text) {
    std::cout << text.get() << std::endl;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << argv[0] << " <data>" << std::endl;
        return 1;
    }

    boost::shared_array<char> text = get(boost::shared_array<char>{argv[1]});
    print(text);
    // delete[] text;

    return 0;
}

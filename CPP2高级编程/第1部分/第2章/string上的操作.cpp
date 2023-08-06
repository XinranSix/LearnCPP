#include <iostream>
#include <string>
#include <vector>

int main(int arvc, char *argv[]) {

    std::string strHello{"Hello!!"};
    std::string strWorld{"The World..."};
    auto position{strHello.find("!!")};
    if (position != std::string::npos) {
        strHello.replace(position, 2, strWorld.substr(3, 6));
    }
    std::cout << strHello << std::endl;

    using namespace std;

    auto string1{"Hello World"};
    auto string2{"Hello World"};

    std::vector names{"John"s, "Sam"s, "Joe"s};

    return 0;
}




#include <iostream>
#include <string>
#include <utility>

std::string getString() { return "Hello World"; }

int main(int arvc, char *argv[]) {

    int x{3}, y{4}, z{5};
    int &xRef{x};

    xRef = 10;
    xRef = y;

    int &zRef{z};
    zRef = xRef;

    // int &emptyRef;

    // const 引用

    int w{};
    int const &wRef{w};
    // wRef = 4;

    // int &unnameRef1{5};
    const int &unnameRef2{5};

    // std::string &string1{getString()};
    std::string const &string2{getString()};

    // 指针的引用和(引用的指针 Error)
    int *intP{nullptr};
    int *&ptrRef{intP};
    ptrRef = new int;
    *ptrRef = 5;

    int k{3};
    int &kRef{k};
    int *xPtr{&xRef};
    *xPtr = 100;

    // 结构化绑定
    std::pair myPair{"hello", 5};
    auto [theString, theInt]{myPair};
    auto &[theString1, theInt1]{myPair};
    auto const &[theString2, theInt2]{myPair};

    // 引用数据成员
    // 必须在构造子中初始化
    class MyClass {
    public:
        MyClass(int &ref) : m_ref(ref) {}

    private:
        int &m_ref;
    };

    return 0;
}

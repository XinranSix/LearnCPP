#include <iostream>
#include <string>
#include <functional>

using namespace std;

class TestBindVar {
public:

    template <typename... T>
    void Init(T &...args) {
        cout << __FUNCTION__ << endl;
        Print(args...);

        // 方法1
        {
            mf_ = std::bind(&TestBindVar::Reset<T &...>, this, args...);
            std::cout << __FUNCTION__ << "==> " << __LINE__ << std::endl;
            mf_();
        }

        // 方法2
        {
            void (TestBindVar::*FuncPointer)(T &...) = &TestBindVar::Reset<T &...>;
            mf_ = std::bind(FuncPointer, this, args...);
            std::cout << __FUNCTION__ << "==> " << __LINE__ << std::endl;
            mf_();
        }

        // 方法3
        {
            using FuncType = void (TestBindVar::*)(T &...);
            mf_ = std::bind(FuncType(&TestBindVar::Reset), this, args...);
            std::cout << __FUNCTION__ << "==> " << __LINE__ << std::endl;
            mf_();
        }
    }

    template <typename... T>
    void Reset(T &...args) {
        cout << __FUNCTION__ << endl;
    }

    // std::function to Reset(...)
    std::function<void()> mf_;

private:
    template <typename First>
    void Print(First &arg) {
        cout << arg << endl;
    }

    template <typename First, typename... Rest>
    void Print(First &arg, Rest &...args) {
        cout << arg << "";
        Print(args...);
    }
};

int main() {
    int arg1 = 1;
    double arg2 = 2.5;
    string arg3 { "test_bind" };

    TestBindVar TestBindVar;
    TestBindVar.Init(arg1, arg2, arg3);

    return 0;
}
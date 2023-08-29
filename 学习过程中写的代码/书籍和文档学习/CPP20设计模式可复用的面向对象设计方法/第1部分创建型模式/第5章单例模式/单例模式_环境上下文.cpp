#include <iostream>
#include <stack>

class Token;

class BuilderContext final {
    int height { 0 };
    BuilderContext() = default;

public:
    static std::stack<BuilderContext> stack;

public:
    static BuilderContext current();

    static Token with_height(int height);
};

std::stack<BuilderContext> BuilderContext::stack { { BuilderContext {} } };

class Token {
public:
    ~Token() {
        if (BuilderContext::stack.size() > 1) {
            BuilderContext::stack.pop();
        }
    }
};

BuilderContext BuilderContext::current() { return stack.top(); }

Token BuilderContext::with_height(int height) {
    auto copy { current() };
    copy.height = height;
    stack.push(copy);
    return Token {};
}

int main(int argc, char *argv[]) { return 0; }

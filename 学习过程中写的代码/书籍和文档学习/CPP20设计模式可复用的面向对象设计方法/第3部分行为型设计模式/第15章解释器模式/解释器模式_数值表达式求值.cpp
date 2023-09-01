#include "boost/lexical_cast.hpp"
#include <cctype>
#include <cstddef>
#include <format>
#include <iostream>
#include <memory>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

struct Token {
    enum Type { integer, plus, minus, lparen, rparen } type;
    std::string text;

    explicit Token(Type type, std::string const &text)
        : type { type }, text { text } {}

    friend std::ostream &operator<<(std::ostream &os, Token const &obj) {
        return os << std::format("`{}`", obj.text);
    }
};

std::vector<Token> lex(std::string const &input) {
    std::vector<Token> result;

    for (int i { 0 }; i < input.size(); ++i) {
        switch (input[i]) {
        case '+':
            result.emplace_back(Token::plus, "+");
            break;
        case '-':
            result.emplace_back(Token::minus, "-");
            break;
        case '(':
            result.emplace_back(Token::lparen, "(");
            break;
        case ')':
            result.emplace_back(Token::rparen, ")");
            break;
        default:
            std::ostringstream buffer;
            buffer << input[i];
            for (int j { i + 1 }; j < input.size(); ++j) {
                if (std::isdigit(input[j])) {
                    buffer << input[j];
                    ++i;
                } else {
                    result.emplace_back(Token::integer, buffer.str());
                    buffer.str("");
                    break;
                }
            }
            if (auto str { buffer.str() }; str.length() > 0) {
                result.emplace_back(Token::integer, str);
            }
        }
    }
    return result;
}

struct Element {
    virtual int eval() const = 0;
};

struct Integer : Element {
    int value;

    explicit Integer(int const value) : value { value } {}

    int eval() const override { return value; }
};

struct BinaryOperation : Element {
    enum Type { addition, minus } type;
    std::shared_ptr<Element> lhs, rhs;

    int eval() const override {
        if (type == addition) {
            return lhs->eval() + rhs->eval();
        }
        return lhs->eval() - rhs->eval();
    }
};

std::shared_ptr<Element> parse(std::vector<Token> const &tokens) {
    auto result { std::make_unique<BinaryOperation>() };
    bool have_lhs = false;
    for (size_t i { 0 }; i < tokens.size(); ++i) {
        auto token { tokens[i] };
        switch (token.type) {
        case Token::integer: {
            int value { boost::lexical_cast<int>(token.text) };
            auto integer { std::make_shared<Integer>(value) };
            if (!have_lhs) {
                result->lhs = integer;
                have_lhs = true;
            } else {
                result->rhs = integer;
            }
        } break;
        case Token::plus:
            result->type = BinaryOperation::addition;
            break;
        case Token::minus:
            result->type = BinaryOperation::minus;
            break;

        case Token::lparen: {
            int j = i;
            for (; j < tokens.size(); ++j) {
                if (tokens[j].type == Token::rparen) {
                    break;
                }
            }

            std::vector<Token> subexpression { &tokens[i + 1], &tokens[j] };
            auto element { parse(subexpression) };
            if (!have_lhs) {
                result->lhs = element;
                have_lhs = true;
            } else {
                result->rhs = element;
            }
            i = j;
        }
        case Token::rparen: {
            
        }
        }
    }
    return result;
}

int main(int argc, char *argv[]) { return 0; }

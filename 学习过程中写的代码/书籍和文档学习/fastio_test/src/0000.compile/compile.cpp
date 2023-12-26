#include <iostream>
#include <cctype>

class Parser {
public:
    int parseExpression(const std::string &input) {
        expression = input;
        pos = 0;
        return parseAddition();
    }

private:
    int parseAddition() {
        int result = parseMultiplication();

        while (pos < expression.length() &&
               (expression[pos] == '+' || expression[pos] == '-')) {
            char op = expression[pos++];
            int nextTerm = parseMultiplication();

            if (op == '+') {
                result += nextTerm;
            } else {
                result -= nextTerm;
            }
        }

        return result;
    }

    int parseMultiplication() {
        int result = parseTerm();

        while (pos < expression.length() &&
               (expression[pos] == '*' || expression[pos] == '/')) {
            char op = expression[pos++];
            int nextFactor = parseTerm();

            if (op == '*') {
                result *= nextFactor;
            } else {
                result /= nextFactor;
            }
        }

        return result;
    }

    int parseTerm() {
        if (isdigit(expression[pos])) {
            return expression[pos++] - '0';
        } else if (expression[pos] == '(') {
            pos++; // Consume '('
            int result = parseAddition();
            pos++; // Consume ')'
            return result;
        } else {
            // Handle error or throw exception
            return 0;
        }
    }

    std::string expression;
    size_t pos;
};

int main() {
    Parser parser;
    std::string input = "3 + 5 * (2 - 6)";
    int result = parser.parseExpression(input);
    std::cout << "Result: " << result << std::endl;

    return 0;
}

#include <iostream>
#include <sstream>
#include <string>

template <typename Visitable>
struct Visitor {
    virtual void visit(Visitable &obj) = 0;
};

struct VisitorBase {
    virtual ~VisitorBase() = default;
};

struct Expression {
    virtual ~Expression() = default;

    virtual void accept(VisitorBase &obj) {
        using EV = Visitor<Expression>;
        if (auto ev { dynamic_cast<EV *>(&obj) }) {
            ev->visit(*this);
        }
    }
};

struct DoubleExpression;
struct AdditionExpression;

struct ExpressionPrinter : VisitorBase,
                           Visitor<DoubleExpression>,
                           Visitor<AdditionExpression> {

    virtual void visit(DoubleExpression &obj) override;
    virtual void visit(AdditionExpression &obj) override;

    std::string str() const { return oss.str(); }
    /*
virtual void visit(AdditionExpression *ae) {
oss << "(";
ae->left->accept(this);
oss << "+";
ae->right->accept(this);
oss << ")";
}
*/
private:
    std::ostringstream oss;
};

/* struct ExpressionVisitor {
    virtual void visit(DoubleExpression *de) = 0;
    virtual void visit(AdditionExpression *ae) = 0;
};
 */
/* struct Expression {
    virtual void accept(ExpressionVisitor *visitor) = 0;
    virtual ~Expression() = default;
};

struct DoubleExpression : Expression {
    double value;
    explicit DoubleExpression(const double value) : value { value } {}

    virtual void accept(ExpressionVisitor *visitor) { visitor->visit(this);
}
};

struct AdditionExpression : Expression {
    Expression *left, *right;

    AdditionExpression(Expression *const left, Expression *const right)
        : left { left }, right { right } {}

    virtual void accept(ExpressionVisitor *visitor) { visitor->visit(this);
}

    ~AdditionExpression() {
        delete left;
        delete right;
    }
};
 */
/*

struct ExpressionEvaluator : ExpressionVisitor {
    double result {};

    virtual void visit(DoubleExpression *de) { result = de->value; }

    virtual void visit(AdditionExpression *ae) {
        ae->left->accept(this);
        auto temp { result };
        ae->right->accept(this);
        result += temp;
    }
}; */

int main(int argc, char *argv[]) {
    /*   auto e { new AdditionExpression {
          new DoubleExpression { 1 },
          new AdditionExpression { new DoubleExpression { 2 },
                                   new DoubleExpression { 3 } } } };

      ExpressionPrinter printer;
      ExpressionEvaluator evaluator;
      printer.visit(e);
      evaluator.visit(e);
      std::cout << printer.str() << " = " << evaluator.result << std::endl;
    */

    return 0;
}

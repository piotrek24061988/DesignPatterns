#include <iostream>
#include <sstream>
using namespace std;

struct DoubleExpression;
struct AdditionExpression;
struct SubstractionExpression;

struct ExpressionVisitor
{
    virtual void visit(DoubleExpression *de) = 0;
    virtual void visit(AdditionExpression *ae) = 0;
    virtual void visit(SubstractionExpression *se) = 0;
};

struct ExpressionPrinter : ExpressionVisitor
{
    ostringstream oss;
    string str() {return oss.str();}

    void visit(DoubleExpression *de) override;
    void visit(AdditionExpression *ae) override;
    void visit(SubstractionExpression *se) override;
};

struct ExpressionEvaluator : ExpressionPrinter
{
    double result;

    void visit(DoubleExpression *de) override;
    void visit(AdditionExpression *ae) override;
    void visit(SubstractionExpression *se) override;
};

struct Expression
{
    virtual void accept(ExpressionVisitor *visitor)
    {

    }
};

struct DoubleExpression : Expression
{
    double value;

    DoubleExpression(double val)
        : value(val)
    {}

    void accept(ExpressionVisitor *visitor) override
    {
        visitor->visit(this);
    }
};

struct AdditionExpression : Expression
{
    Expression * left, * right;

    AdditionExpression(Expression * l, Expression * r)
        : left(l), right(r)
    {}

    ~AdditionExpression()
    {
        if(left)
        {
            delete left;
        }
        if(right)
        {
            delete right;
        }
    }

    void accept(ExpressionVisitor *visitor) override
    {
        visitor->visit(this);
    }
};

struct SubstractionExpression : Expression
{
    Expression * left, * right;

    SubstractionExpression(Expression * l, Expression * r)
        : left(l), right(r)
    {}

    ~SubstractionExpression()
    {
        if(left)
        {
            delete left;
        }
        if(right)
        {
            delete right;
        }
    }

    void accept(ExpressionVisitor *visitor) override
    {
        visitor->visit(this);
    }
};

void ExpressionPrinter::visit(DoubleExpression *de)
{
    oss << de->value;
}
void ExpressionPrinter::visit(AdditionExpression *ae)
{
    bool need_braces = dynamic_cast<SubstractionExpression*>(ae->right);
    if(need_braces)
    {
        oss << "(";
    }
    ae->left->accept(this);
    oss << "+";
    ae->right->accept(this);
    if(need_braces)
    {
        oss << ")";
    }
}

void ExpressionPrinter::visit(SubstractionExpression *se)
{
    bool need_braces = dynamic_cast<SubstractionExpression*>(se->right);
    if(need_braces)
    {
        oss << "(";
    }
    se->left->accept(this);
    oss << "-";
    se->right->accept(this);
    if(need_braces)
    {
        oss << ")";
    }
}

void ExpressionEvaluator::visit(DoubleExpression *de)
{
    result = de->value;
}
void ExpressionEvaluator::visit(AdditionExpression *ae)
{
    ae->left->accept(this);
    auto temp = result;
    ae->right->accept(this);
    result += temp;
}

void ExpressionEvaluator::visit(SubstractionExpression *se)
{
    se->left->accept(this);
    auto temp = result;
    se->right->accept(this);
    result = temp - result;
}

int main()
{
    auto e = AdditionExpression{ new DoubleExpression{1}, new SubstractionExpression{new DoubleExpression{2}, new DoubleExpression{3}}};
    ExpressionPrinter ep;
    ep.visit(&e);
    cout << ep.str() << endl;

    ExpressionEvaluator evaluator;
    evaluator.visit(&e);
    cout << ep.str() << " = " << evaluator.result;

    return 0;
}

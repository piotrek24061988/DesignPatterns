#include <iostream>
#include <sstream>
using namespace std;

template <typename Visitable>
struct Visitor
{
    virtual void visit(Visitable & obj) = 0;
};

struct VisitorBase
{
    virtual ~VisitorBase() = default;
};

struct Expression
{
    virtual ~Expression() = default;

    virtual void accept(VisitorBase & obj)
    {
        using EV = Visitor<Expression>;
        if(auto ev = dynamic_cast<EV*>(&obj))
        {
            ev->visit(*this);
        }
    }
};

struct DoubleExpression : Expression
{
    double value;

    DoubleExpression(double val) : value(val){}

    void accept(VisitorBase & obj) override
    {
        using DEV = Visitor<DoubleExpression>;
        if(auto dev = dynamic_cast<DEV*>(&obj))
        {
            dev->visit(*this);
        }
    }
};

struct AdditionExpression : Expression
{
    Expression * left, *right;

    AdditionExpression(Expression * l, Expression * r)
        : left(l), right(r)
    {
    }

    ~AdditionExpression()
    {
        delete left;
        delete right;
    }

    void accept(VisitorBase & obj) override
    {
        using AEV = Visitor<AdditionExpression>;
        if(auto aev = dynamic_cast<AEV*>(&obj))
        {
            aev->visit(*this);
        }
    }
};

struct ExpressionPrinter : VisitorBase, Visitor<DoubleExpression>, Visitor<AdditionExpression>
{
    void visit(DoubleExpression & obj) override
    {
        oss << obj.value;
    }

    void visit(AdditionExpression & obj) override
    {
        oss << "(";
        obj.left->accept(*this);
        oss << "+";
        obj.right->accept(*this);
        oss << ")";
    }

    string str(){return oss.str();}

private:
    ostringstream oss;

};

int main()
{
    auto e = AdditionExpression{ new DoubleExpression{1}, new AdditionExpression{new DoubleExpression{2}, new DoubleExpression{3}}};

    ExpressionPrinter ep;
    ep.visit(e);
    cout << ep.str() << endl;


    return 0;
}


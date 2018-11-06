#include <iostream>
#include <sstream>
using namespace std;

struct Expression
{
    virtual ~Expression() = default;
};

struct DoubleExpression : Expression
{
    double value;

    DoubleExpression(double val)
        : value(val)
    {}
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
};

struct ExpressionPrinter
{
    ostringstream oss;

    string str(){ return oss.str();}

    void print(Expression * e)
    {
        if(auto de = dynamic_cast<DoubleExpression*>(e))
        {
            oss << de->value;
        }
        else if(auto ae = dynamic_cast<AdditionExpression*>(e))
        {
            oss << "(";
            print(ae->left);
            oss << "+";
            print(ae->right);
            oss << ")";
        }
        else
        {
            oss << "not found ";
        }
    }
};

int main()
{
    auto e = new AdditionExpression{new DoubleExpression{1}, new AdditionExpression{new DoubleExpression{2}, new DoubleExpression{3}}};
    ExpressionPrinter ep;
    ep.print(e);
    cout << ep.str() << endl;

    delete e;
    return 0;
}

#include <iostream>
#include <sstream>
using namespace std;

struct Expression
{
    virtual ~Expression() = default;
    virtual void print(ostringstream & os) = 0;
};

struct DoubleExpression : Expression
{
    double value;

    DoubleExpression(double val)
        : value(val)
    {}

    void print(ostringstream &os) override
    {
        os << value;
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

    void print(ostringstream &os) override
    {
        os << "(";
        left->print(os);
        os << "+";
        right->print(os);
        os << ")";
    }
};

int main()
{
    auto e = new AdditionExpression{new DoubleExpression{1}, new AdditionExpression{new DoubleExpression{2}, new DoubleExpression{3}}};

    ostringstream oss;
    e->print(oss);
    cout << oss.str() << endl;

    delete e;
    return 0;
}


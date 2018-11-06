#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <boost/lexical_cast.hpp>
//using namespace boost;
using namespace std;

struct Token
{
    enum Type {integer, plus, minus, lparen, rparen} type;
    string text;

    Token(Type type_, const string & text_) : type(type_), text(text_){}

    friend ostream & operator<<(ostream & os, const Token & token)
    {
        os << "'" << token.text << "'";
        return os;
    }
};

vector<Token> lex(const string & str)
{
    vector<Token> result;

    for(int i = 0; i < str.size(); i++)
    {
        switch (str[i])
        {
        case '+':
            result.push_back(Token {Token::plus, "+"});
            break;
        case '-':
            result.push_back(Token {Token::minus, "-"});
            break;
        case '(':
            result.push_back(Token {Token::lparen, "("});
            break;
        case ')':
            result.push_back(Token {Token::rparen, ")"});
            break;
        default:
            ostringstream buffer;
            buffer << str[i];
            for(int j = i + 1; j < str.size(); j++)
            {
                if(isdigit(str[j]))
                {
                    buffer << str[j];
                    i++;
                }
                else
                {
                    result.push_back(Token{Token::integer, buffer.str()});
                    break;
                }
            }
            break;
        }
    }

    return result;
}

struct Element
{
    virtual int eval() = 0;
};

struct Integer : Element
{
    int value;

    Integer(const int & val)
        : value(val)
    {}

    int eval() override
    {
        return value;
    }
};

struct BinaryOperation : Element
{
    enum Type {addition, subtraction} type;
    std::shared_ptr<Element> rhs, lhs;

    int eval() override
    {
        auto left = lhs->eval();
        auto right = rhs->eval();
        if(type == addition)
        {
            return left + right;
        }
        else
        {
            return left - right;
        }
    }
};

std::shared_ptr<Element> parse(const vector<Token> & tokens)
{
    auto result = make_unique<BinaryOperation>();
    bool have_lhs{false};

    for(int i = 0; i < tokens.size(); i++)
    {
        auto & token = tokens[i];
        switch(token.type)
        {
            case Token::integer:
            {
                int value = boost::lexical_cast<int>(token.text);
                auto integer = make_shared<Integer>(value);
                if(!have_lhs)
                {
                    result->lhs = integer;
                    have_lhs = true;
                }
                else
                {
                    result->rhs = integer;
                }
                break;
            }
            case Token::plus:
                result->type = BinaryOperation::addition;
                break;
            case Token::minus:
                result->type = BinaryOperation::subtraction;
                break;
            case Token::lparen:
            {
                int j = i;
                for(; j < tokens.size(); ++j)
                {
                    if(tokens[j].type == Token::rparen)
                    {
                        break;
                    }
                }

                vector<Token> subexpression(&tokens[i+1], &tokens[j]);
                auto element = parse(subexpression);
                if(!have_lhs)
                {
                    result->lhs = element;
                    have_lhs = true;
                }
                else
                {
                    result->rhs = element;
                }
                i = j;
                break;
            }
            case Token::rparen:
                break;
            default:
                break;
        }
    }
    return result;
}

int main()
{
    string input{"(13-4)-(12+1)"};

    vector<Token> tokens = lex(input);
    for(auto & a : tokens)
    {
        cout << a;
    }
    cout << endl;

    try
    {
        auto parsed = parse(tokens);
        cout << input << " = " << parsed->eval() << endl;
    }
    catch(...)
    {

    }
    {
        string input{"(13+4)+(12-1)"};

        vector<Token> tokens = lex(input);
        for(auto & a : tokens)
        {
            cout << a;
        }
        cout << endl;

        try
        {
            auto parsed = parse(tokens);
            cout << input << " = " << parsed->eval() << endl;
        }
        catch(...)
        {

        }
    }

    return 0;
}


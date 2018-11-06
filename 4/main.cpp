#include <iostream>
using namespace std;


//Against interface segragation solid principle
/*
struct Imachine
{
    virtual void print() = 0;
    virtual void scan() = 0;
};

struct printer : public Imachine
{
    void print() override
    {
        //some sensfull code
    }

    void scan() override
    {

    }
};

struct scanner : public Imachine
{
    void print() override
    {
    }

    void scan() override
    {
        //some sensfull code
    }
};

struct machine : public Imachine
{
    void print() override
    {
        //some sensfull code
    }

    void scan() override
    {
        //some sensfull code
    }
};
*/

struct Iprinter
{
    virtual void print() = 0;
};

struct Iscaner
{
    virtual void scan() = 0;
};

struct printer : public Iprinter
{
    void print() override
    {
        //some sensfull code
    }
};

struct scanner : public Iscaner
{
    void scan() override
    {
        //some sensfull code
    }
};

struct machine : public Iscaner, public Iprinter
{
    void print() override
    {
        //some sensfull code
    }

    void scan() override
    {
        //some sensfull code
    }
};

int main()
{
    machine m;
    return 0;
}


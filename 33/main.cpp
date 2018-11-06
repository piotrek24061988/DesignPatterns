#include <iostream>
using namespace std;

struct Pingable
{
    virtual string ping(const string & message) = 0;
};

struct Pong : Pingable
{
    string ping(const string & message) override
    {
        return message + " pong";
    }
};

void tryIt(Pingable & p)
{
    cout << p.ping("ping") << endl;
}

int main()
{
    Pong pp;
    for(int i = 0; i < 3; i++)
    {
        tryIt(pp);
    }

    return 0;
}


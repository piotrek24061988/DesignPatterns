#include <iostream>
using namespace std;

class Memento
{
    int ballance;
public:
    Memento(int ballance_) : ballance(ballance_)
    {}

    int getBallance() const
    {
        return ballance;
    }
};

class BankAccount
{
   int ballance;
public:
    BankAccount(int ballance_) : ballance(ballance_)
    {}

    Memento deposit(int ammount)
    {
        ballance += ammount;
        return {ballance};
    }

    void restore(const Memento & m)
    {
        ballance = m.getBallance();
    }

    friend ostream & operator<<(ostream & os, const BankAccount & b)
    {
        os << "ballance: " << b.ballance << endl;
    }
};

int main()
{
    BankAccount ba{100};
    cout << ba;
    auto m1 = ba.deposit(50);
    cout << ba;
    auto m2 = ba.deposit(25);
    cout << ba;
    ba.deposit(12);
    cout << ba;

    ba.restore(m2);
    cout << ba;
    ba.restore(m1);
    cout << ba;

    return 0;
}


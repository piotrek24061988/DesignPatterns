#include <iostream>
#include <vector>
#include <memory>
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

class BankAccount2
{
    int ballance{0};
    vector<shared_ptr<Memento>> changes;
    int current;

public:
    BankAccount2(int ballance_)
        : ballance(ballance_)
    {
        changes.push_back(make_shared<Memento>(ballance));
        current = 0;
    }

    shared_ptr<Memento> deposit(int val)
    {
        ballance += val;
        auto m = make_shared<Memento>(ballance);
        changes.push_back(m);
        ++current;
        return m;
    }

    void restore(const shared_ptr<Memento>& m)
    {
        if(m)
        {
            ballance = m->getBallance();
            changes.push_back(m);
            current = changes.size() - 1;
        }
    }

    shared_ptr<Memento> undo()
    {
        if(current > 0)
        {
            current--;
            auto m = changes[current];
            ballance = m->getBallance();
            return m;
        }
        return {};
    }

    shared_ptr<Memento> redo()
    {
        if(current + 1 < changes.size())
        {
            ++current;
            auto m = changes[current];
            ballance = m->getBallance();
            return m;
        }
        return {};
    }

    friend ostream & operator<<(ostream & os, const BankAccount2 & b)
    {
        os << "ballance: " << b.ballance << endl;
    }
};

int main()
{
    BankAccount2 ba{100};
    ba.deposit(50);
    cout << ba;
    ba.deposit(25);
    cout << ba;
    ba.undo();
    cout << ba;
    ba.undo();
    cout << ba;
    ba.redo();
    cout << ba;

    return 0;
}

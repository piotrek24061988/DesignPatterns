#include <iostream>
#include <vector>
using namespace std;

struct BankAccount
{
    int ballance{0};
    int overdraft_limit{-500};

    void deposit(int val)
    {
        ballance += val;
        cout << "deposited: " << val << ", and ballance is now: " << ballance << endl;
    }

    bool withdraw(int val)
    {
        if(ballance - val >= overdraft_limit)
        {
            ballance -= val;
            cout << "withdrawed: " << val << ", and ballance is now: " << ballance << endl;
            return true;
        }
        return false;
    }

    friend ostream & operator<<(ostream & os, BankAccount & ba)
    {
        os << "bank deposite: " << ba.ballance << endl;
    }
};

struct Command
{
    bool succesed;
    virtual void call() = 0;
    virtual void undo() = 0;
};

struct BankAccountCommand : Command
{
    BankAccount & account;
    enum Acction {deposit, withdraw} acction;
    int ammount;

    BankAccountCommand(BankAccount & account_, Acction acction_, int ammount_)
        : account(account_), acction(acction_), ammount(ammount_)
    {
        succesed = false;
    }

    void call() override
    {
        switch(acction)
        {
            case deposit:
                account.deposit(ammount);
                succesed = true;
                break;
            case withdraw:
                succesed = account.withdraw(ammount);
                break;
            default:
                break;
        }
    }

    void undo() override
    {
        if(! succesed)
        {
            return;
        }

        switch(acction)
        {
            case deposit:
                account.withdraw(ammount);
                break;
            case withdraw:
                account.deposit(ammount);
                break;
            default:
                break;
        }
    }
};

struct CompositeBankAccountCommand : vector<BankAccountCommand>, Command
{
    CompositeBankAccountCommand(const initializer_list<BankAccountCommand> & ilist)
        : vector(ilist)
    {}

    void call() override
    {
        for(auto & cmd : *this)
        {
            cmd.call();
        }
    }

    void undo() override
    {
        for(auto it = rbegin(); it != rend(); ++it)
        {
            it->undo();
        }
    }
};

struct DependendCompositeCommand : CompositeBankAccountCommand
{
    DependendCompositeCommand(const initializer_list<BankAccountCommand> & items)
        : CompositeBankAccountCommand(items)
    {}

    void call() override
    {
        bool ok = true;
        for(auto & cmd : *this)
        {
            if(ok)
            {
                cmd.call();
                ok = cmd.succesed;
            }
            else
            {
                cmd.succesed = false;
            }
        }
    }
};

struct MoneyTransferCommand : DependendCompositeCommand
{
    MoneyTransferCommand(BankAccount & from, BankAccount & to, int ammount)
        : DependendCompositeCommand(
        {
              BankAccountCommand{from, BankAccountCommand::withdraw, ammount},
              BankAccountCommand{to, BankAccountCommand::deposit, ammount}
        })
    {}
};

int main()
{
    BankAccount ba, ba2;
    ba.deposit(200);

    cout << "bank1: " << ba << ", bank2: " << ba2 << endl;

    MoneyTransferCommand cmd{ba, ba2, 120};
    cmd.call();
    cout << "bank1: " << ba << ", bank2: " << ba2 << endl;

    cmd.undo();
    cout << "bank1: " << ba << ", bank2: " << ba2 << endl;

    cout << endl << endl << endl;

    BankAccount bb, bb2;
    bb.deposit(200);

    cout << "bank1: " << bb << ", bank2: " << bb2 << endl;

    MoneyTransferCommand cmd2{bb, bb2, 5000};
    cmd2.call();
    cout << "bank1: " << bb << ", bank2: " << bb2 << endl;

    cmd2.undo();
    cout << "bank1: " << bb << ", bank2: " << bb2 << endl;

    return 0;
}


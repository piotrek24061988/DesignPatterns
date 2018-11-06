#include <iostream>
#include <string>
using namespace std;

struct Creature
{
    string name;
    int attack, defence;

    Creature(const string & name_, const int & attack_, const int & defence_)
        : name(name_), attack(attack_), defence(defence_)
    {}

    friend ostream & operator<<(ostream & os, const Creature & creature)
    {
        os << "name: " << creature.name << ", attack: " << creature.attack << ", defence: " << creature.defence << endl;
    }
};

class CreatureModifier
{
    CreatureModifier * next{nullptr};
protected:
    Creature & creature;
public:
    CreatureModifier(Creature & creature_)
        : creature{creature_}
    {}

    void add(CreatureModifier *cm)
    {
        if(next)
        {
            next->add(cm);
        }
        else
        {
            next = cm;
        }
    }

    virtual void handle()
    {
        if(next)
        {
            next->handle();
        }
    }
};

class DoubleAttackModifier : public CreatureModifier
{
public:
    DoubleAttackModifier(Creature & creature)
        : CreatureModifier(creature)
    {}

    void handle() override
    {
        creature.attack *= 2;
        CreatureModifier::handle();//chain of responsibility
    }
};

class IncreaseDeffenceModifier : public CreatureModifier
{
public:
    IncreaseDeffenceModifier(Creature & creature)
        : CreatureModifier(creature)
    {}

    void handle() override
    {
        if(creature.attack <= 2)
        {
            creature.defence++;
        }
        CreatureModifier::handle();//chain of responsibility
    }
};

class NoBonusesModifier : public CreatureModifier
{
public:
    NoBonusesModifier(Creature & creature)
        : CreatureModifier(creature)
    {}

    void handle() override
    {
    }
};

int main()
{
    Creature goblin{"Goblin", 1, 1};
    CreatureModifier root{goblin};
    DoubleAttackModifier r1{goblin};
    IncreaseDeffenceModifier r2{goblin};
    cout << goblin;
    r1.handle();
    cout << goblin;
    r2.handle();
    cout << goblin;

    cout << endl;

    Creature goblin2{"Goblin", 1, 1};
    CreatureModifier root2{goblin2};
    DoubleAttackModifier r12{goblin2};
    IncreaseDeffenceModifier r22{goblin2};
    root2.add(&r12);
    root2.add(&r22);
    cout << goblin2;
    root2.handle();
    cout << goblin2;

    cout << endl;
    Creature goblin3{"Goblin", 1, 1};
    CreatureModifier root3{goblin3};
    DoubleAttackModifier r13{goblin2};
    IncreaseDeffenceModifier r23{goblin3};
    NoBonusesModifier r33{goblin3};
    root3.add(&r33);
    root3.add(&r13);
    root3.add(&r23);
    cout << goblin3;
    root3.handle();
    cout << goblin3;

    return 0;
}


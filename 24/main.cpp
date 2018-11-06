#include <iostream>
#include <algorithm>
#include <list>
#include <set>
#include <array>
#include <numeric>
using namespace std;

//class Creature
//{
//    int strength, agility, inteligence;
//public:

//    int getStrength() const
//    {
//        return strength;
//    }

//    void setStrength(int s)
//    {
//        strength = s;
//    }

//    int getAgility() const
//    {
//        return agility;
//    }

//    void setAgility(int a)
//    {
//        agility = a;
//    }

//    int getInteligence() const
//    {
//        return inteligence;
//    }

//    void setInteligence(int i)
//    {
//        inteligence = i;
//    }

//    int sum() const
//    {
//        return strength + agility + inteligence;
//    }

//    int average() const
//    {
//        return (strength + agility + inteligence)/3;
//    }

//    int maxim() const
//    {
//        return max(max(strength, agility), inteligence);
//    }
//};

class Creature
{
    enum Abilities {stre, agil, intel, count};
    array<int, count> abilities;
public:

    int getStrength() const
    {
        return abilities[stre];
    }

    void setStrength(int s)
    {
        abilities[stre] = s;
    }

    int getAgil() const
    {
        return abilities[agil];
    }

    void setAgil(int s)
    {
        abilities[agil] = s;
    }

    int getIntel() const
    {
        return abilities[intel];
    }

    void setIntel(int s)
    {
        abilities[intel] = s;
    }

    int sum() const
    {
        return accumulate(abilities.begin(), abilities.end(), 0);
    }

    int avg() const
    {
        return sum() / count;
    }

    int max() const
    {
        return *max_element(abilities.begin(), abilities.end());
    }
};

int main()
{
    Creature orc;
    orc.setStrength(80);
    orc.setAgil(30);
    orc.setIntel(10);

    cout << orc.sum() << endl;
    cout << orc.max() << endl;
    cout << orc.avg() << endl;

    return 0;
}


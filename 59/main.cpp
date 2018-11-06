#include <iostream>
#include <sstream>
#include <typeindex>
#include <map>
using namespace std;

struct GameObject;

void collide(GameObject & first, GameObject & second);

struct GameObject
{
    virtual type_index type() const = 0;

    void collide(GameObject & other)
    {
        ::collide(*this, other);
    }
};

template <typename T>
struct GameObjectImpl : GameObject
{
    type_index type() const override
    {
        return typeid(T);
    }
};

struct Plannet : GameObjectImpl<Plannet>
{

};

struct Asteroid : GameObjectImpl<Asteroid>
{

};

struct Spaceship : GameObjectImpl<Spaceship>
{

};

void spaceship_plannet()
{
    cout << "spaceship land on a plannet" << endl;
}

void asteroid_plannet()
{
    cout << "asteroid burns up in the atmosphere" << endl;
}

void asteroid_spaceship()
{
    cout << "asteroid hits and destroyed spaceship" << endl;
}

map<pair<type_index, type_index>, void(*)()> outcomes
{
    {{typeid(Spaceship), typeid(Plannet)}, spaceship_plannet},
    {{typeid(Asteroid), typeid(Plannet)}, asteroid_plannet},
    {{typeid(Asteroid), typeid(Spaceship)}, asteroid_spaceship}
};

void collide(GameObject & first, GameObject & second)
{
    auto it = outcomes.find({first.type(), second.type()});
    if(it == outcomes.end())
    {
       it = outcomes.find({second.type(), first.type()});
       if(it == outcomes.end())
       {
           cout << "objects pass each other harmresly" << endl;
           return;
       }
    }
    it->second();
}

int main()
{
    Asteroid a;
    Plannet p;
    Spaceship s;

    collide(s, p);
    collide(s, a);
    collide(s, s);

    return 0;
}

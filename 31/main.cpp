#include <iostream>
using namespace std;

template <typename T>
struct Property
{
    T value;

    Property(T value_)
//        : value{value_}
    {
        *this = value_;
    }

    T & operator=(const T & new_value)
    {
        cout << "own operator= working" << endl;
        return value = new_value;
    }

    operator T()
    {
        cout << "own operator T working" << endl;
        return value;
    }
};

struct Creature
{
    Property<int> strength{10};
    Property<int> agility{11};
};

int main()
{
    Creature c;
    c.strength = 11;
    c.agility = 15;

    int x = c.agility;
    cout << x << endl;

    return 0;
}


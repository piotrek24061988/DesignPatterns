#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector<string> names {"Piotr", "Madzia", "Kasia", "Przemek", "Ania"};
    vector<string>::iterator it = names.begin();
    cout << "First name is: " << *it << endl;

    it++;
    it->append(" Cwiklinska");
    cout << "Second name is: " << *it << endl;

    while(++it != names.end())
    {
        cout << *it << endl;
    }

    for(auto it = names.rbegin(); it != names.rend(); it++)
    {
        cout << *it << endl;
    }

    vector<string>::const_reverse_iterator Ania = names.crbegin();
    cout << *Ania << endl;

    for(auto & name : names)
    {
        cout << name << endl;
    }

    return 0;
}


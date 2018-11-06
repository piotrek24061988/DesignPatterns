#include <iostream>
#include <string>
#include <map>
#include <boost/bimap.hpp>
#include <boost/flyweight.hpp>

using namespace std;
using namespace boost;

typedef uint32_t key;

struct User
{
public:
    User(const string & fn, const string & ln)
        : first_name{add(fn)}, last_name{add(ln)}
    {
    }

    const string & getFirstName() const
    {
        return names.left.find(first_name)->second;
    }

    const string & getLastName() const
    {
        return names.left.find(last_name)->second;
    }

protected:
    key first_name, last_name;
    static bimap<key, string> names;
    static key seed;

    static key add(string s)
    {
        auto it = names.right.find(s);
        if(it == names.right.end())
        {
            key id = seed++;
            names.insert({id, s});
            return id;
        }
        return it->second;
    }

    friend ostream & operator<<(ostream & os, const User & user);
};

key User::seed{0};
bimap<key, string> User::names{};

ostream & operator<<(ostream & os, const User & user)
{
    os << "first name: " << user.getFirstName() << "[" << user.first_name << "]"
       << ", last name: " << user.getLastName() << "[" << user.last_name << "]";
    return os;
}

struct User2
{
    flyweight<string> first_name, last_name;

    User2(const string & fn, const string & ln)
        : first_name(fn), last_name(ln)
    {
    }
};


int main()
{
    User u1{"John", "Dou"};
    User u2{"John", "Smith"};

    cout << u1 << endl;
    cout << u2 << endl;

    User2 u3("Jack", "Daniels");
    User2 u4("Jack", "Chan");

    cout << u3.first_name << ", " << u3.last_name << endl;
    cout << u4.first_name << ", " << u4.last_name << endl;
    return 0;
}


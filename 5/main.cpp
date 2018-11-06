#include <iostream>
#include <string>
#include <vector>
#include <tuple>
using namespace std;

enum class Relationship
{
    parent,
    child,
    sibling
};

struct Person
{
    string name;
};

struct RelationshipBrowser
{
    virtual vector<Person> find_all_children_of(const string & name) = 0;
};

struct Relationships : RelationshipBrowser //low level module
{
    vector<tuple<Person, Relationship, Person>> relations;

    void add_parent_and_child(const Person & parent, const Person & child)
    {
        relations.push_back({parent, Relationship::parent, child});
        relations.push_back({child, Relationship::child, parent});
    }

    vector<Person> find_all_children_of(const string &name)
    {
        vector<Person> res;
        for(auto & x : relations)
        {
            Person par, chl;
            Relationship rel;
            std::tie(par, rel, chl) = x;
            if((par.name == name) && (rel == Relationship::parent))
            {
                res.push_back(chl);
            }
        }
        return res;
    }
};

struct Research //high level module
{
    Research(RelationshipBrowser & rel)
    {
        for(auto & x : rel.find_all_children_of("John"))
        {
            cout << "John has a child called " << x.name << endl;
        }
    }

/* against D solid principle
    Research(Relationships & rel)
    {
        auto & relations = rel.relations;
        for(auto & x : relations)
        {
            Person par, chl;
            Relationship rel;
            std::tie(par, rel, chl) = x;
            if((par.name == "John") && (rel == Relationship::parent))
            {
                cout << "John has a child called " << chl.name << endl;
            }
        }
    }
*/
};

int main()
{
    Person parent {"John"};
    Person child1 {"Chris"}, child2 {"Matt"};

    Relationships relations;
    relations.add_parent_and_child(parent, child1);
    relations.add_parent_and_child(parent, child2);

    Research _{relations};
    return 0;
}


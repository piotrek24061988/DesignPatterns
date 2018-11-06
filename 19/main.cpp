#include <iostream>
#include <string>
using namespace std;

class Person
{
public:
    string name;

    class PersonImp;
    PersonImp * imp;

    Person(string name_);
    ~Person();

    void greet();
};

class Person::PersonImp
{
public:
    void greet(Person * p)
    {
        cout << "Hello, my name is: " << p->name << endl;
    }
};

Person::Person(string name_) : imp(new PersonImp), name(name_)
{}
Person::~Person(){
    if(imp) delete imp;
}

void Person::greet()
{
    imp->greet(this);
}

int main()
{
    Person p("Erik");
    p.greet();
    return 0;
}


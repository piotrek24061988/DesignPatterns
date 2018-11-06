#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <boost/signals2.hpp>
using namespace std;
using namespace boost;
using namespace boost::signals2;

template <typename T>
struct Observer
{
    virtual void field_changed(T & source, const string & field_name) = 0;
};

template <typename T>
struct Observable
{
    vector<Observer<T>*> observers;

    void notify(T & source, const string & field_name)
    {
        for(auto observer : observers)
        {
            observer->field_changed(source, field_name);
        }
    }

    void subscribe(Observer<T> & observer)
    {
        observers.push_back(&observer);
    }

    void unsubscribe(Observer<T> & observer)
    {
        observers.erase(remove(observers.begin(), observers.end(), &observer), observers.end());
    }
};

class Person : public Observable<Person>
{
    int age;
public:
    Person(int i)
        : age(i)
    {}

    void set_age(int i)
    {
        if(age == i)
        {
            return;
        }
        age = i;
        notify(*this, "age");
    }

    int get_age() const
    {
        return age;
    }
};

struct ConsolePersorObserver : Observer<Person>
{
  void field_changed(Person & source, const string & field_name) override
  {
    cout << "Person's" << field_name << " has changed to ";
    if(field_name == "age")
    {
        cout << source.get_age();
    }
    cout << endl;
  }
};

template <typename T>
struct Observable2
{
    signal<void(T&, const string &)> field_changed;
};

class Person2 : public Observable2<Person2>
{
    int age;
public:
    int get_age() const
    {
        return age;
    }
    void set_age(int i)
    {
        if(age == i)
        {
            return;
        }
        age = i;
        field_changed(*this, "age");
    }
};

int main()
{
    Person2 person;
    auto conn = person.field_changed.connect([](Person2 & p, const string & field_name){
        cout << field_name << " has changed" << endl;
    });
    person.set_age(10);
    person.set_age(11);
    conn.disconnect();
    person.set_age(12);

    return 0;
}

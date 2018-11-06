#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <mutex>
#include <thread>
using namespace std;


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

template <typename T>
struct SaferObservable
{
    recursive_mutex m;

    vector<Observer<T>*> observers;

    void notify(T & source, const string & field_name)
    {
        unique_lock<recursive_mutex> lock(m);
        for(auto observer : observers)
        {
            observer->field_changed(source, field_name);
        }
    }

    void subscribe(Observer<T> & observer)
    {
        unique_lock<recursive_mutex> lock(m);
        observers.push_back(&observer);
    }

    void unsubscribe(Observer<T> & observer)
    {
        unique_lock<recursive_mutex> lock(m);
        observers.erase(remove(observers.begin(), observers.end(), &observer), observers.end());
    }
};

class Person : public SaferObservable<Person>
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

        auto old_can_vote = get_can_vote();
        age = i;
        notify(*this, "age");

        if(old_can_vote != get_can_vote())
        {
            notify(*this, "can_vote");
        }
    }

    int get_age() const
    {
        return age;
    }

    bool get_can_vote()
    {
        return age >= 18;
    }
};

struct ConsolePersorObserver : Observer<Person>
{
  void field_changed(Person & source, const string & field_name) override
  {
    cout << "Person's " << field_name << " has changed to ";
    if(field_name == "age")
    {
        cout << source.get_age();
    }
    if(field_name == "can_vote")
    {
        cout << boolalpha << source.get_can_vote();
    }
    cout << endl;
  }
};

struct TrafficAdministration : Observer<Person>
{
    void field_changed(Person & source, const string & field_name) override
    {
        if(field_name == "age")
        {
            if(source.get_age() < 17)
            {
                cout << "You are not old enough to drive" << endl;
            }
            else
            {
                cout << "Oh ok we no longer care" << endl;
                source.unsubscribe(*this);
            }
        }
    }
};

int main()
{
    Person person{10};
    TrafficAdministration ta;
    person.subscribe(ta);

    person.set_age(15);
    person.set_age(16);
    person.set_age(17);
    person.set_age(18);
    person.set_age(17);
    person.set_age(16);
    person.set_age(15);

    return 0;
}

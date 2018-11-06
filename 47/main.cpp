#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
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

int main()
{
    Person person{10};
    ConsolePersorObserver obs1;
    ConsolePersorObserver obs2;
    person.subscribe(obs1);
    person.subscribe(obs2);
    person.set_age(11);
    person.set_age(11);
    person.set_age(18);
    person.set_age(16);
    person.set_age(15);
    person.unsubscribe(obs1);
    person.set_age(19);
    person.unsubscribe(obs2);
    person.set_age(16);
    person.set_age(15);
    return 0;
}


#include <iostream>
#include <algorithm>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <tuple>
#include <sstream>
#include <memory>
#include <cmath>
#include <map>
#include <functional>
#include <cstdint>
using namespace std;

struct ChatRoom;

struct Person
{
    string name;
    ChatRoom * room{nullptr};
    vector<string> chat_log;

    Person(const string & name_)
        : name(name_)
    {}

    void say(const string & message) const;
//    {
//        room->broadcast(name, message);
//    }

    void pm(const string & who, const string & message) const;
//    {
//        room->message(name, who, message);
//    }

    void receive(const string & origin, const string & message);
//    {
//        string s{origin + ": \"" + message + "\""};
//        cout << s << endl;
//    }

    bool operator==(const Person & rhs);
//    {
//        return name == rhs.name;
//    }

    bool operator!=(const Person & rhs);
//    {
//        return name != rhs.name;
//    }
};

struct ChatRoom
{
    vector<Person*> people;

    void broadcast(const string & origin, const string & message)
    {
        for(auto p : people)
        {
            if(p->name != origin)
            {
                p->receive(origin, message);
            }
        }
    }

    void join(Person * p)
    {
        string join_msg = p->name + " joins the chat";
        broadcast("room", join_msg);
        p->room = this;
        people.push_back(p);
    }

    void message(const string & origin, const string & who, const string & message)
    {
        auto target = find_if(people.begin(), people.end(), [&](Person * p){return p->name == who;});
        if(target != people.end())
        {
            (*target)->receive(origin, message);
        }
    }
};

void Person::say(const string & message) const
{
    room->broadcast(name, message);
}

void Person::pm(const string & who, const string & message) const
{
    room->message(name, who, message);
}

void Person::receive(const string & origin, const string & message)
{
    string s{origin + ": \"" + message + "\""};
    cout << name << "chat session: " << s << endl;
    chat_log.emplace_back(s);
}

bool Person::operator==(const Person & rhs)
{
    return name == rhs.name;
}

bool Person::operator!=(const Person & rhs)
{
    return name != rhs.name;
}

int main()
{
    ChatRoom cr;
    Person John{"John"}, Jane{"Jane"};

    cr.join(&John);
    cr.join(&Jane);
    John.say("hello room");
    Jane.say("welcome");

    Person Simon("Simon");
    cr.join(&Simon);
    Simon.say("Good morning");

    Jane.pm("Simon", "Hi Simon");
    return 0;

}


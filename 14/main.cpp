#include <iostream>
#include <memory>
#include <map>
#include <functional>
#include <string>
#include <cstdlib>
#include <fstream>
#include <vector>
using namespace std;

class Database
{
public:
    virtual int get_population(const string & name) = 0;
};

class DummyDatabase : public Database
{
private:
    map<string, int> populations;
public:
    DummyDatabase()
    {
        populations["alpha"] = 1;
        populations["beta"] = 2;
        populations["gamma"] = 3;
    }

    int get_population(const string &name) override
    {
        return populations[name];
    }
};

class SingletonDatabse : public Database
{
    SingletonDatabse()
    {
        cout << "Initializing database" << endl;
        ifstream ifs("capitals.txt");
        string s1, s2;

        while(getline(ifs, s1))
        {
            getline(ifs, s2);
            int pop = atoi(s2.c_str());
            capitals[s1] = pop;
        }
    }
    map<string, int> capitals;
public:
    SingletonDatabse(const SingletonDatabse & s) = delete;
    void operator=(const SingletonDatabse & s) = delete;

    static SingletonDatabse & get()
    {
        static SingletonDatabse db;
        return db;
    }

    int get_population(const string & name) override
    {
        return capitals[name];
    }
};

struct SingletonRecordFinder
{
    int total_poulation(vector<string> names)
    {
        int res = 0;
        for(auto & name : names)
        {
            res += SingletonDatabse::get().get_population(name);
        }
        return res;
    }
};

struct ConfigRecordFinder
{
    Database & db;

    ConfigRecordFinder(Database & d) : db(d)
    {}

    int total_poulation(vector<string> names)
    {
        int res = 0;
        for(auto & name : names)
        {
            res += db.get_population(name);
        }
        return res;
    }
};

int main()
{
    string city{"Tokyo"};
    int pop = SingletonDatabse::get().get_population(city);
    cout << "city: " << city << " has population: ";
    cout << pop << endl;

    vector<string> names {"Tokyo", "Delhi"};
    SingletonRecordFinder srf1;
    cout << "cities Tokyo and Delhi have population1: " << srf1.total_poulation(names) << endl;

    ConfigRecordFinder crf1(SingletonDatabse::get());
    cout << "cities Tokyo and Delhi have population2: " << crf1.total_poulation(names) << endl;

    vector<string> names2 {"alpha", "beta"};
    DummyDatabase ddb;
    ConfigRecordFinder crf2(ddb);
    cout << "cities aplha and betha have population3: " << crf2.total_poulation(names2) << endl;

    return 0;
}


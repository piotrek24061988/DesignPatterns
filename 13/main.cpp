#include <iostream>
#include <memory>
#include <map>
#include <functional>
#include <string>
#include <cstdlib>
#include <fstream>
#include <vector>
using namespace std;

class SingletonDatabse
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

    int get_population(const string & name)
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

int main()
{
    string city{"Tokyo"};
    int pop = SingletonDatabse::get().get_population(city);
    cout << "city: " << city << " has population: ";
    cout << pop << endl;

    return 0;
}


#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

class Journal
{
private:
    string title;
    vector<string> entries;
public:
    Journal(const string & tit)
        : title{tit}
    {}

    void add_entry(const string & entry)
    {
        static int count;
        entries.push_back(to_string(count++) + ": " + entry);
    }

    vector<string> getEntries() const
    {
        return entries;
    }

    //break solid rule srp
    //void save(const string & filename)
    //{
    //    ofstream ofs(filename);
    //    for(auto & x : entries)
    //    {
    //        ofs << x << endl;
    //    }
    //}
};

class Persistence
{
public:
    static void save(const Journal & j, const string & filename)
    {
        ofstream ofs(filename);
        for(auto & x : j.getEntries())
        {
            ofs << x << endl;
        }
    }
};

int main()
{
    Journal journal{"Dear Diary"};
    journal.add_entry("I ate a bug");
    journal.add_entry("I lov dev");

    //break solid rule srp
    //Journal.save("file.tmp")
    Persistence::save(journal, string("file.tmp"));

    return 0;
}


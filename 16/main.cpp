#include <iostream>
using namespace std;

class Printer
{
    static int id;
public:
    int get_id() const {return id;}
    void set_id(int value){id = value;}
};

int Printer::id = 0;

int main()
{
    Printer p;
    p.set_id(1);
    cout << p.get_id() << endl << endl;

    Printer p2;
    p2.set_id(2);
    cout << p.get_id() << endl;
    cout << p2.get_id() << endl;

    return 0;
}


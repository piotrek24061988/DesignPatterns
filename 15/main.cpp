#include <iostream>
#include <memory>
#include "di.h"

using namespace std;

struct IFoo
{
    virtual string name() = 0;
};

struct Foo : IFoo
{
    static int id;
    Foo(){++id;}

    string name() override
    {
        return "Foo: " + to_string(id);
    }
};

int Foo::id = 0;

struct Bar
{
    shared_ptr<IFoo> foo;
};

int main()
{
    auto injector = make_injector(boost::di::bind<IFoo>().to<Foo>().in(boost::di::singleton));

    auto bar1 = injector.create<shared_ptr<Bar>>();
    auto bar2 = injector.create<shared_ptr<Bar>>();

    cout << bar1->foo->name() << endl;
    cout << bar2->foo->name() << endl;

    return 0;
}


#include <iostream>
#include <vector>
using namespace std;

struct GraphicsObject
{
    virtual void draw() = 0;
};

struct Circle : GraphicsObject
{
    void draw() override
    {
        cout << "Circle" << endl;
    }
};

struct Group : GraphicsObject
{
    string name;
    vector<GraphicsObject *> objects;

    Group(const string name_) : name(name_){}

    void draw() override
    {
        cout << "Group " << name << " contains: " << endl;
        for(auto & object : objects)
        {
            object->draw();
        }
    }
};

int main()
{
    Group root("root");
    Circle c1, c2, c3;
    root.objects.push_back(&c1);

    Group subgroup("sub");
    subgroup.objects.push_back(&c2);
    subgroup.objects.push_back(&c3);

    root.objects.push_back(&subgroup);

    root.draw();
    return 0;
}


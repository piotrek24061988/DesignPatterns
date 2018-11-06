#include <iostream>
#include <sstream>
#include <string>
using namespace std;

struct Shape
{
    virtual string str() const = 0;
};

struct Circle : Shape
{
    float radius;

    Circle() : radius(0.0){}
    Circle(float radius_) : radius(radius_){}

    string str() const override
    {
        ostringstream oss;
        oss << "Circle with the radius: " << radius;
        return oss.str();
    }

    void resize(float factor)
    {
        radius *= factor;
    }
};

struct Square : Shape
{
    float side;

    Square() : side(0.0){}
    Square(float side_) : side(side_){}

    string str() const override
    {
        ostringstream oss;
        oss << "Square with the side: " << side;
        return oss.str();
    }

    void resize(float factor)
    {
        side *= factor;
    }
};

struct ColoredShape : Shape
{
    Shape & shape;
    string color;

    ColoredShape(Shape & shape_, string color_) : shape(shape_), color(color_){}

    string str() const override
    {
        ostringstream oss;
        oss << shape.str() << ", has a color: " << color;
        return oss.str();
    }
};

struct TransparentShape : Shape
{
    Shape & shape;
    int transparency;

    TransparentShape(Shape & shape_, int transparency_) : shape(shape_), transparency(transparency_){}

    string str() const override
    {
        ostringstream oss;
        oss << shape.str() << ", has transparency level: " << transparency;
        return oss.str();
    }
};

int main()
{
    Square sq{5};
    cout << sq.str() << endl;
    ColoredShape cs{sq, "red"};
    cout << cs.str() << endl;
    TransparentShape ts(cs, 80);
    cout << ts.str() << endl;

    return 0;
}


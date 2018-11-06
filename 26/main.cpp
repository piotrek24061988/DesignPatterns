#include <iostream>
#include <sstream>
#include <string>
#include <assert.h>
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

template <typename T>
struct ColoredShape2 : T
{
    static_assert(is_base_of<Shape, T>::value, "Template argument must be a shape");
    string color;

    ColoredShape2(){}

    //TransparentShape2<ColoredShape2<Squre>> sq(10, "red", 80);
    template <typename...Args>
    ColoredShape2(string color_, Args ...args) : T(forward<Args>(args)...), color(color_){}

    string str() const override
    {
        ostringstream oss;
        oss << T::str() << ", has a color: " << color;
        return oss.str();
    }
};

template <typename T>
struct TransparentShape2 : T
{
    static_assert(is_base_of<Shape, T>::value, "Template argument must be a shape");
    int transparency;

    TransparentShape2(){}

    //TransparentShape2<ColoredShape2<Squre>> sq(10, "red", 80);
    template <typename...Args>
    TransparentShape2(int transparency_, Args ...args) : T(forward<Args>(args)...), transparency(transparency_){}

    string str() const override
    {
        ostringstream oss;
        oss << T::str() << ", has a transparency: " << transparency;
        return oss.str();
    }
};

int main()
{
    ColoredShape2<Circle> green_circle{"green", 5};
    green_circle.resize(4.4);
    cout << green_circle.str() << endl;

    TransparentShape2<ColoredShape2<Circle>> transparent_green_circle{80, "green", 5};
    transparent_green_circle.resize(5.5);
    cout << transparent_green_circle.str() << endl;

    return 0;
}


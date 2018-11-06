#include <iostream>
#include <cmath>
using namespace std;

/*
enum class PointType {cart, polar};

class Point
{
public:
    Point(float a, float b, PointType typ = PointType::cart)
    {
        if(typ == PointType::cart)
        {
            x = a;
            y = b;
        }
        else
        {
            x = a * cos(b);
            y = a * sin(b);
        }
    }

private:
    float x, y;
};

*/

enum class PointType
{
    cartesian,
    polar
};

class Point
{
public:
    static Point newCartesian(float x, float y)
    {
        return {x, y};
    }

    static Point newPolar(float r, float t)
    {
        return {r*cos(t), t*sin(t)};
    }

    friend ostream & operator<<(ostream & os, const Point & p)
    {
        os << "x: " << p.x << ", y: " << p.y << endl;
    }

private:
    Point(float x1, float y1) : x(x1), y(y1){}
    float x, y;
};

int main()
{
    auto p = Point::newCartesian(2, 3);
    auto q = Point::newPolar(4, 5);

    cout << p << endl;
    cout << q << endl;

    return 0;
}


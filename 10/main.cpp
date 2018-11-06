#include <iostream>
#include <cmath>
using namespace std;

enum class PointType
{
    cartesian,
    polar
};

class Point
{
public:

    friend ostream & operator<<(ostream & os, const Point & p)
    {
        os << "x: " << p.x << ", y: " << p.y << endl;
    }

private:

    struct PointFactory
    {
        static Point newCartesian(float x, float y)
        {
            return {x, y};
        }

        static Point newPolar(float r, float t)
        {
            return {r*cos(t), t*sin(t)};
        }
    };

    Point(float x1, float y1) : x(x1), y(y1){}
    float x, y;

public:
     static PointFactory Factory;
};



int main()
{
    auto p = Point::Factory.newCartesian(2, 3);
    auto q = Point::Factory.newPolar(4, 5);

    cout << p << endl;
    cout << q << endl;

    return 0;
}


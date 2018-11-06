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
    Point(float x1, float y1) : x(x1), y(y1){}

    friend ostream & operator<<(ostream & os, const Point & p)
    {
        os << "x: " << p.x << ", y: " << p.y << endl;
    }

private:
    float x, y;
};

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

int main()
{
    auto p = PointFactory::newCartesian(2, 3);
    auto q = PointFactory::newPolar(4, 5);

    cout << p << endl;
    cout << q << endl;

    return 0;
}

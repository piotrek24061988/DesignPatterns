#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <boost/functional/hash.hpp>
using namespace std;

struct Point
{
    int x, y;

    friend size_t hash_value(const Point & obj)
    {
        size_t seed = 0x1E44943F;
        boost::hash_combine(seed, obj.x);
        boost::hash_combine(seed, obj.y);
        return seed;
    }
};

struct Line
{
    Point start, end;

    friend size_t hash_value(const Line & obj)
    {
        size_t seed = 0x4D274623;
        boost::hash_combine(seed, obj.start);
        boost::hash_combine(seed, obj.end);
        return seed;
    }
};

struct VectorObject
{
    virtual vector<Line>::iterator begin() = 0;
    virtual vector<Line>::iterator end() = 0;
};

struct VectorRectangle : VectorObject
{
public:
    VectorRectangle(int x, int y, int width, int height)
    {
        lines.emplace_back(Line {Point{x, y}, Point{x + width, y}});
        lines.emplace_back(Line {Point{x + width, y}, Point{x + width, y + height}});
        lines.emplace_back(Line {Point{x, y}, Point{x, y + height}});
        lines.emplace_back(Line {Point{x, y + height}, Point{x + width, y + height}});
    }

    vector<Line>::iterator begin() override
    {
        return lines.begin();
    }

    vector<Line>::iterator end() override
    {
        return lines.end();
    }

private:
    vector<Line> lines;
};

void DrawPoints(vector<Point>::iterator start, vector<Point>::iterator end)
{
    for(auto i = start; i != end; ++i)
    {
        cout << "p.x: " << i->x << ", p.y: " << i->y << endl;
    }
}

vector<shared_ptr<VectorObject>> vectorObjects
{
    make_shared<VectorRectangle>(10, 10, 100, 100),
    make_shared<VectorRectangle>(30, 30, 60, 60)
};

struct LineToPointAdapter
{
    using Points = vector<Point>;

    LineToPointAdapter(Line & line)
    {
        static int count = 0;

        int left = min(line.start.x, line.end.x);
        int right = max(line.start.x, line.end.x);
        int top = min(line.start.y, line.end.y);
        int bottom = max(line.start.y, line.end.y);
        int dx = right - left;
        int dy = line.end.y - line.start.y;

        if(dx == 0)
        {
            for(int y = top; y<= bottom; ++y)
            {
                points.emplace_back(Point{left, y});
            }
        }
        else if(dy == 0)
        {
            for(int x = left; x <= right; ++x)
            {
                points.emplace_back(Point{x, top});
            }
        }
    }

    Points::iterator begin() {return points.begin();}
    Points::iterator end() {return points.end();}

private:
    Points points;
};

struct LineToPointCachingAdapter
{
    using Points = vector<Point>;

    LineToPointCachingAdapter(Line & line)
    {
        boost::hash<Line> hash;
        line_hash = hash(line);
        if(cache.find(line_hash) != cache.end()) return;

        static int count = 0;

        Points points;
        int left = min(line.start.x, line.end.x);
        int right = max(line.start.x, line.end.x);
        int top = min(line.start.y, line.end.y);
        int bottom = max(line.start.y, line.end.y);
        int dx = right - left;
        int dy = line.end.y - line.start.y;

        if(dx == 0)
        {
            for(int y = top; y<= bottom; ++y)
            {
                points.emplace_back(Point{left, y});
            }
        }
        else if(dy == 0)
        {
            for(int x = left; x <= right; ++x)
            {
                points.emplace_back(Point{x, top});
            }
        }

        cache[line_hash] = points;
    }

    Points::iterator begin() {return cache[line_hash].begin();}
    Points::iterator end() {return cache[line_hash].end();}
private:
    size_t line_hash;
    static map<size_t, Points> cache;
};

map<size_t, LineToPointCachingAdapter::Points> LineToPointCachingAdapter::cache;

int main()
{
    for(auto & vectorObject : vectorObjects)
    {
        for(auto & line : *vectorObject)
        {
            LineToPointAdapter ltpa {line};
            DrawPoints(ltpa.begin(), ltpa.end());
        }
    }

    cout << endl << endl << endl;

    for(auto & vectorObject : vectorObjects)
    {
        for(auto & line : *vectorObject)
        {
            LineToPointCachingAdapter ltpa {line};
            DrawPoints(ltpa.begin(), ltpa.end());
        }
    }
    return 0;
}

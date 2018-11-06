#include <iostream>
using namespace std;

class Rectangle
{
protected:
    int width, height;
public:
    Rectangle(int w, int h)
        : width(w), height(h)
    {
    }

    virtual int getWidth() const
    {
        return width;
    }

    virtual int getHeight() const
    {
        return height;
    }

    virtual void setWidth(int a)
    {
        width = a;
    }

    virtual void setHeight(int a)
    {
        height = a;
    }

    virtual int area()
    {
        return width * height;
    }
};

void process(Rectangle & r)
{
    int w = r.getWidth();
    r.setHeight(10);

    cout << "expected area: " << w * 10 << endl;
    cout << "curent area: " << r.area() << endl;
}

class Square : public Rectangle
{
public:
    Square(int size)
        : Rectangle(size, size)
    {}

    void setWidth(int w) override
    {
        width = height = w;
    }

    void setHeight(int h) override
    {
        width = height = h;
    }
};

int main()
{
    Rectangle r{3, 4};
    Square s{4};
    process(r);
    process(s);

    return 0;
}


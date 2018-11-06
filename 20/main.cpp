#include <iostream>
using namespace std;

// Shapes - circle, square
// Render - raster, vector

struct Renderer
{
    virtual void render_circle(float x, float y, float radius) = 0;
};

struct VectorRenderer : Renderer
{
    void render_circle(float x, float y, float radius) override
    {
        cout << "vector rendering circle of radius " << radius << endl;
    }
};

struct RasterRenderer : Renderer
{
    virtual void render_circle(float x, float y, float radius) override
    {
        cout << "raster rendering circle of radius " << radius << endl;
    }
};

struct Shape
{
protected:
    Renderer & renderer;
    Shape(Renderer & renderer_) : renderer(renderer_){}
public:
    virtual void draw() = 0;
    virtual void resize(float factor) = 0;
};

struct Circle : Shape
{
    float x, y, radius;

    Circle(Renderer & renderer_, float x_, float y_, float radius_)
        : Shape(renderer_), x(x_), y(y_), radius(radius_)
    {}

    void draw() override
    {
        renderer.render_circle(x, y, radius);
    }

    void resize(float factor) override
    {
        radius *= factor;
    }
};

int main()
{
    RasterRenderer rr;
    Circle raster_circle(rr, 5, 5, 5);
    raster_circle.draw();
    raster_circle.resize(5);
    raster_circle.draw();

    cout << endl << endl;

    VectorRenderer vr;
    Circle vector_circle(vr, 5, 5, 5);
    vector_circle.draw();
    vector_circle.resize(5);
    vector_circle.draw();
    return 0;
}


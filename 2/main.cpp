#include <iostream>
#include <string>
#include <memory>
#include <vector>
using namespace std;

enum class Color {red, green, blue};
enum class Size {small, medium, large};

struct Product
{
    string name;
    Color color;
    Size size;
};

template <typename T>
struct Specification
{
    virtual bool is_satisfied(T * item) = 0;
};

template <typename T>
struct Filter
{
    virtual vector<T*> filter(vector<T*> items, Specification<T> & spec) = 0;
};

struct BetterFilter : Filter<Product>
{
    vector<Product*> filter(vector<Product*> items, Specification<Product> & spec) override
    {
        vector<Product*> results;
        for(auto & item : items)
        {
            if(spec.is_satisfied(item))
            {
                results.push_back(item);
            }
        }
        return results;
    }
};

struct ColorSpecification : Specification<Product>
{
private:
    Color color;
public:
    ColorSpecification(Color col)
        : color(col)
    {}

    bool is_satisfied(Product *item) override
    {
        return (color == item->color);
    }
};

struct SizeSpecification : Specification<Product>
{
private:
    Size size;
public:
    SizeSpecification(Size s)
        : size(s)
    {}

    bool is_satisfied(Product *item) override
    {
        return (size == item->size);
    }
};

struct AndSpecification : Specification<Product>
{
private:
    Specification<Product> & spec1;
    Specification<Product> & spec2;

public:
    AndSpecification(Specification<Product> & s1, Specification<Product> & s2)
        : spec1(s1), spec2(s2)
    {}

    bool is_satisfied(Product *item) override
    {
        return (spec1.is_satisfied(item) && spec2.is_satisfied(item));
    }
};

int main()
{
    Product apple {"apple", Color::green, Size::small};
    Product tree {"tree", Color::green, Size::large};
    Product house {"house", Color::blue, Size::large};

    vector<Product*> items {&apple, &tree, &house};

    BetterFilter bf;
    ColorSpecification green {Color::green};
    SizeSpecification large {Size::large};

    for(auto & item : bf.filter(items, green))
    {
        cout << item->name << " is green" << endl;
    }

    for(auto & item : bf.filter(items, large))
    {
        cout << item->name << " is large" << endl;
    }

    AndSpecification green_and_large(green, large);
    for(auto & item : bf.filter(items, green_and_large))
    {
        cout << item->name << " is green and large" << endl;
    }

    return 0;
}


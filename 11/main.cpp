#include <iostream>
#include <memory>
#include <map>
#include <functional>
using namespace std;

struct HotDrink
{
    virtual void prepare(int volume) = 0;
    virtual ~HotDrink() = default;
};

struct Tea : HotDrink
{
    void prepare(int volume) override
    {
        cout << "take a tea bag" << endl;
        cout << "boild water" << endl;
        cout << "pour " << volume << " ml" << endl;
        cout << "add some lemon" << endl;
    }
};

struct Coffee : HotDrink
{
    void prepare(int volume) override
    {
        cout << "grind some beans" << endl;
        cout << "boil water" << endl;
        cout << "pour " << volume << " ml" << endl;
        cout << "add some milk" << endl;
    }
};

struct HotDrinkFactory //AF
{
    virtual unique_ptr<HotDrink> make() const = 0;
};

struct TeaFactory : HotDrinkFactory
{
    unique_ptr<HotDrink> make() const override
    {
        return make_unique<Tea>();
    }
};

struct CoffeeFactory : HotDrinkFactory
{
    unique_ptr<HotDrink> make() const override
    {
        return make_unique<Coffee>();
    }
};

struct DrinkFactory
{
    map<string, unique_ptr<HotDrinkFactory>> hot_factories;
public:
    DrinkFactory()
    {
        hot_factories["coffee"] = make_unique<CoffeeFactory>();
        hot_factories["tea"] = make_unique<TeaFactory>();
    }

    unique_ptr<HotDrink> make_drink(const string & name)
    {
        auto drink = hot_factories[name]->make();
        drink->prepare(200);
        return drink;
    }
};

struct DrinkWithVolumeFactory
{
    map<string, function<unique_ptr<HotDrink>()>> factories;
public:
    DrinkWithVolumeFactory()
    {
        factories["tea"] = [](){
            auto tea = make_unique<Tea>();
            tea->prepare(200);
            return tea;
        };
        factories["coffee"] = [](){
            auto coffee = make_unique<Coffee>();
            coffee->prepare(200);
            return coffee;
        };
    }

    unique_ptr<HotDrink> make_drink(const string & type)
    {
        return factories[type]();
    }
};

unique_ptr<HotDrink> make_drink(string type)
{
    unique_ptr<HotDrink> drink;

    if(type == "tea")
    {
        drink = make_unique<Tea>();
        drink->prepare(200);
    }
    else
    {
        drink = make_unique<Coffee>();
        drink->prepare(200);
    }
    return drink;
}

int main()
{
    auto a = make_drink("tea");

    cout << endl << endl;

    DrinkFactory df;
    df.make_drink("coffee");

    cout << endl << endl;

    DrinkWithVolumeFactory dwvf;
    dwvf.make_drink("tea");

    return 0;
}

//24

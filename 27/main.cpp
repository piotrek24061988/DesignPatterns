#include <iostream>
#include <functional>
#include <string>
using namespace std;

struct Logger
{
    function<void()> func;
    string name;

    Logger(const function<void()> & func_, const string & name_)
        : func(func_), name(name_)
    {

    }

    void operator()() const
    {
        cout << "Entering " << name << endl;
        func();
        cout << "Exiting " << name << endl;
    }
};

template <typename Func>
struct Logger2
{
    Func func;
    string name;

    Logger2(const Func & func_, const string & name_)
        : func(func_), name(name_)
    {

    }

    void operator()() const
    {
        cout << "Entering " << name << endl;
        func();
        cout << "Exiting " << name << endl;
    }
};

template <typename Func>
auto make_loger2(const Func & func, const string & name)
{
    return Logger2<Func>{func, name};
}

double add(double a, double b)
{
    cout << a << " + " << b << " = " << (a + b) << endl;
    return a + b;
}

template <typename> struct Logger3;

template<typename R, typename ...Args>
struct Logger3<R(Args...)>
{
    function<R(Args...)> func;
    string name;

    Logger3(const function<R(Args...)> & func_, const string & name_) : func(func_), name(name_)
    {}

    R operator()(Args ...args)
    {
        cout << "Entering " << name << endl;
        R result = func(args...);
        cout << "Exiting " << name << endl;
        return result;
    }
};

template <typename R, typename ...Args>
auto make_logger3(R (*func)(Args...), const string & name)
{
    return Logger3<R(Args...)>(function<R(Args...)>(func), name);
}

int main()
{
    Logger([](){cout << "Hello World!" << endl;}, "Hello Funcion")();

    cout << endl;
    //Logger2([](){cout << "Hello World!" << endl;}, "Hello Funcion")();
    Logger2<function<void()>>([](){cout << "Hello World!" << endl;}, "Hello Funcion2")();

    cout << endl;

    auto log2 = make_loger2([](){cout << "Hello World!" << endl;}, "Hello Funcion3");
    log2();

    cout << endl;

    auto log3 = make_logger3(add, "Add Function 1");
    auto result = log3(2, 3);
    cout << "res at the end: " << result << endl;

    return 0;
}


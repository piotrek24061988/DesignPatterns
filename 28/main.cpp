#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;

class Window
{
public:
    void show()
    {
        cout << "Window" << endl;
    }

    void doSomething(int i)
    {
        cout << i << endl;
    }
};

class Console
{
public:
    static Console & instance()
    {
        static Console console;
        return console;
    }

    vector<shared_ptr<Window>> windows;
    shared_ptr<Window> multicolumn(const string & title, uint8_t columnCount, uint8_t columnWidth, uint8_t charsHigh)
    {
        auto w = make_shared<Window>();
        return w;
    }

private:
    const int charWidth = 10;
    const int charHeight = 14;
    Console(){}
    Console(const Console & other) = delete;
    Console & operator=(const Console & other) = delete;
};

int main()
{
    auto window = Console::instance().multicolumn("Test", 2, 40, 40);

    for(size_t i = 0; i < 40; i++)
    {
        window->doSomething(i);
    }

    window->show();

    return 0;
}


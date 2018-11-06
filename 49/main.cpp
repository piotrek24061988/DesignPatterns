#include <iostream>
using namespace std;

struct LightSwitch;

struct State
{
    virtual void on(LightSwitch * lhs)
    {
        cout << "light is already on" << endl;
    }

    virtual void off(LightSwitch * lhs)
    {
        cout << "light is already off" << endl;
    }
};

struct OnState : State
{
    OnState()
    {
        cout << "Light is turned on" << endl;
    }

    virtual void off(LightSwitch * lhs);
};

struct OffState : State
{
    OffState()
    {
        cout << "Light is turned off" << endl;
    }

    virtual void on(LightSwitch * lhs);
};

struct LightSwitch
{
    State * state;
public:
    LightSwitch()
    {
        state = new OffState();
    }

    void setState(State * s)
    {
        state = s;
    }

    void on()
    {
        state->on(this);
    }

    void off()
    {
        state->off(this);
    }
};

void OnState::off(LightSwitch * lhs)
{
    cout << "Switching light off" << endl;
    //this->off(lhs);
    lhs->setState(new OffState());
    delete this;
}

void OffState::on(LightSwitch * lhs)
{
    cout << "Switching light on" << endl;
    //this->on(lhs);
    lhs->setState(new OnState());
    delete this;
}

int main()
{
    LightSwitch ls;
    ls.on();
    ls.on();
    ls.off();
    ls.off();

    return 0;
}


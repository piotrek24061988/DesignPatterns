#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std;

enum class State
{
    off_hook,
    conecting,
    connected,
    on_hold,
    on_hook
};

ostream & operator<<(ostream & os, State & state)
{
    switch(state)
    {
    case State::off_hook:
        os << "off the hook";
        break;
    case State::conecting:
         os << "connecting";
        break;
    case State::connected:
         os << "connected";
        break;
    case State::on_hold:
         os << "on hold";
        break;
    case State::on_hook:
        os << "on the hook";
        break;
    default:
        break;
    }
    return os;
}

enum class Triger
{
    call_dialed,
    hang_up,
    call_connected,
    placed_on_hold,
    taken_off_hold,
    left_message,
    stop_using_phone
};

ostream & operator<<(ostream & os, Triger & state)
{
    switch(state)
    {
    case Triger::call_dialed:
        os << "call dialed";
        break;
    case Triger::hang_up:
        os << "hang up";
        break;
    case Triger::call_connected:
         os << "call connected";
        break;
    case Triger::placed_on_hold:
         os << "placed on hold";
        break;
    case Triger::taken_off_hold:
        os << "taken off hold";
        break;
    case Triger::left_message:
        os << "left message";
        break;
    case Triger::stop_using_phone:
        os << "stop using phone";
        break;
    default:
        break;
    }
    return os;
}


int main()
{
    map<State, vector<pair<Triger, State>>> rules;

    rules[State::off_hook] = {
        {Triger::call_dialed, State::conecting},
        {Triger::stop_using_phone, State::on_hook}
    };

    rules[State::conecting] = {
        {Triger::hang_up, State::off_hook},
        {Triger::call_connected, State::connected}
    };

    rules[State::connected] = {
        {Triger::left_message, State::off_hook},
        {Triger::hang_up, State::off_hook},
        {Triger::placed_on_hold, State::on_hold}
    };

    rules[State::on_hold] = {
        {Triger::taken_off_hold, State::connected},
        {Triger::hang_up, State::off_hook}
    };

    State currentState{State::off_hook}, exitState{State::on_hook};

    while(true)
    {
        cout << "The phone is currently " << currentState << endl;

    select_triger:
        cout << "Select a triger" << endl;
        int i = 0;
        for(auto item : rules[currentState])
        {
            cout << i++ << ", " << item.first << endl;
        }

        int input;
        cin >> input;
        if(input < 0 || (input + 1) > rules[currentState].size())
        {
            cout << "Incorrect option, please try again" << endl;
            goto select_triger;
        }
        currentState = rules[currentState][input].second;
        if(currentState == exitState)
        {
            break;
        }
    }

    return 0;
}


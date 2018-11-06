#include <iostream>
#include <string>
#include <vector>
//back - end
#include <boost/msm/back/state_machine.hpp>
//front - end
#include <boost/msm/front/state_machine_def.hpp>
#include <boost/msm/front/functor_row.hpp>
using namespace std;
namespace msm = boost::msm;
namespace mpl = boost::mpl;
using namespace msm::front;

vector<string> state_names
{
    "off hook",
    "connecting",
    "connected",
    "on hold",
    "destroyed"
};

struct CallDialed {};
struct HangUp {};
struct CallConnected {};
struct PlacedOnHold {};
struct TakenOffHold {};
struct LeftMessage {};
struct PhoneThrownIntoWall {};

struct PhoneStateMachine : state_machine_def<PhoneStateMachine>
{
    bool angry{true};

    struct OffHook : state<>{};
    struct Connecting : state<>
    {
      template <typename Event, typename FSM>
      void on_entry(const Event & event, FSM & fsm)
      {
        cout << "We are conecting..." << endl;
      }
    };
    struct Connected : state<>{};
    struct OnHold : state<>{};
    struct PhoneDestroyed : state<>{};
    struct PhoneBeingDestroyed
    {
        template<typename EVT, typename FSM, typename SourceState, typename TargetState>
        void operator()(EVT & evt, FSM & fsm, SourceState & ss, TargetState & ts)
        {
            cout << "Phone breaks into milion pieces" << endl;
        }
    };

    struct CanDestroyPhone
    {
        template<typename EVT, typename FSM, typename SourceState, typename TargetState>
        bool operator()(EVT & evt, FSM & fsm, SourceState & ss, TargetState & ts)
        {
            return fsm.angry;
        }
    };

    struct transition_table : mpl::vector
    <
        Row<OffHook, CallDialed, Connecting>,
        Row<Connecting, CallConnected, Connected>,
        Row<Connected, PlacedOnHold, OnHold>,
        Row<OnHold, PhoneThrownIntoWall, PhoneDestroyed, PhoneBeingDestroyed, CanDestroyPhone>
    >{};

    typedef OffHook initial_state;
    template <typename FSM, typename Event>
    void no_transition(Event & e, FSM &, int state)
    {
        cout << "No transition from state " << state_names[state]
             << " on event " << typeid(e).name() << endl;
    }
};

int main()
{
    msm::back::state_machine<PhoneStateMachine> phone;

    auto info = [&]()
    {
        auto i = phone.current_state()[0];
        cout << "The phone is currently " << state_names[i] << endl;
    };

    info();
    phone.process_event(CallDialed{});
    info();
    phone.process_event(CallConnected{});
    info();
    phone.process_event(PlacedOnHold{});
    info();
    phone.process_event(PhoneThrownIntoWall{});
    info();
    phone.process_event(CallConnected{});

    return 0;
}


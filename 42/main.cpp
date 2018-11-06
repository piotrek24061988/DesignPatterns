#include <iostream>
#include <string>
#include <boost/signals2.hpp>
using namespace std;
using namespace boost;
using namespace boost::signals2;

struct EventData
{
    virtual void print() const = 0;
};

struct PlayerScoredData : EventData
{
    string player_name;
    int goals_scored_so_far;

    PlayerScoredData(const string & player, int & goals)
        : player_name(player), goals_scored_so_far(goals)
    {}

    void print() const override
    {
        cout << player_name << " has scored a goals: " << goals_scored_so_far << endl;
    }
};

struct Game
{
    signal<void(EventData*)> events;
};

struct Player
{
    string name;
    int goals_scored{0};
    Game& game;

    Player(const string & name_, Game & game_)
        : name(name_), game(game_)
    {

    }

    void score()
    {
        goals_scored++;
        PlayerScoredData ps{name, goals_scored};
        game.events(&ps);
    }
};

struct Coach
{
    Game & game;

    Coach(Game & game_)
        : game(game_)
    {
        game.events.connect([](EventData * e){PlayerScoredData * ps = dynamic_cast<PlayerScoredData*>(e); if(ps){cout << "well done " << ps->player_name << endl;}});
    }
};

int main()
{
    Game game;
    Player player1{"Sam", game};
    Player player2{"Matt", game};

    Coach coach{game};

    player1.score();
    player1.score();
    player2.score();
    return 0;
}


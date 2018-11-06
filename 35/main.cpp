#include <iostream>
#include <boost/signals2.hpp>
using namespace std;
using namespace boost;
using namespace boost::signals2;

struct Query
{
    string creature_name;
    enum Argument {attack, defense} argument;
    int result;

    Query(const string & creature_name_, Argument argument_, int result_)
        : creature_name{creature_name_}, argument{argument_}, result{result_}
    {}
};

struct Game //mediator
{
    signal<void(Query &)> queries;
};

struct Creature
{
    Game & game;
    int attack, defense;
    string name;

    Creature(Game & game_, const int & attack_, const int & defense_, const string & name_)
        : game(game_), attack(attack_), defense(defense_), name(name_)
    {}

    int get_attack() const
    {
        Query q{name, Query::Argument::attack, attack};
        game.queries(q);
        return q.result;
    }

    int get_defense() const
    {
        Query q{name, Query::Argument::defense, defense};
        game.queries(q);
        return q.result;
    }

    friend ostream & operator<<(ostream & os, const Creature & c)
    {
        os << "atack: " << c.get_attack() << ", defense: " << c.get_defense() << ", name: " << c.name;
        return os;
    }
};

 class CreatureModifier
 {
    Game & game;
    Creature & creature;
 public:
    CreatureModifier(Game & game_, Creature & creature_) : game(game_), creature(creature_)
    {}

    virtual ~CreatureModifier() = default;
 };

 class DoubleAttackModifier : public CreatureModifier
 {
     connection conn;
public:
     DoubleAttackModifier(Game & game_, Creature & creature_) : CreatureModifier(game_, creature_)
     {
         conn =  game_.queries.connect([&](Query & q){
             if(q.creature_name == creature_.name && q.argument == Query::Argument::attack)
             {
                 q.result *= 2;
             }
             if(q.creature_name == creature_.name && q.argument == Query::Argument::defense)
             {
                 q.result *= 3;
             }
         });
     }

     ~DoubleAttackModifier()
     {
         conn.disconnect();
     }
 };


int main()
{
    Game game;
    Creature goblin(game, 2, 2, "Strong Goblin");
    cout << goblin << endl;

    {
        DoubleAttackModifier dam{game, goblin};
        cout << goblin << endl;
    }
    cout << goblin << endl;

    return 0;
}


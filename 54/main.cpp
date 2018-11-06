#include <iostream>
#include <string>
using namespace std;

class Game
{
public:
    Game(int nop)
        : number_of_players(nop)
    {}

    void run()
    {
        start();
        while(!have_winner())
        {
            take_turn();
        }
        cout << "Player " << get_winner() << " wins" << endl;
    }

protected:
    virtual void start() = 0;
    virtual bool have_winner() = 0;
    virtual void take_turn() = 0;
    virtual int get_winner() = 0;

    int current_player{0};
    int number_of_players;
};

class Chess : public Game
{
public:
    Chess()
        : Game(2)
    {
        cout << "ChessGame" << endl;
    }

protected:
    void start() override
    {
        cout << "Starting game of chess with " << number_of_players << " players" << endl;
    }
    bool have_winner() override
    {
        return turn == max_turns;
    }
    void take_turn() override
    {
        cout << "Turn " << turn << " taken by player " << current_player + 1 << endl;
        ++turn;
        current_player = (current_player + 1) % number_of_players;
    }
    int get_winner() override
    {
        current_player = (current_player + 1) % number_of_players;
        return current_player + 1;
    }
private:
    int turn {0};
    int max_turns{10};
};

int main()
{
    Chess chess;
    chess.run();

    return 0;
}


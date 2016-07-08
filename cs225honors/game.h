#ifndef _GAME_H_
#define _GAME_H_

#include <iterator>
#include <ostream>
#include <algorithm>
#include "list.h"

using namespace std;


class Game
{
public:
    Game(int n);
    Game( const Game & other );
    Game & operator=( const Game & rhs );
    ~Game();
    void move(int dir);
    int score();
    void print() const;
    char* grid;
    List<int> changes;
    
private:
    int side;
    int headx;
    int heady;
    List<int> red;
    List<int> green;
    bool redalive;
    
    
    void nextApple();
    void copy(const Game & other);
    int nextTile(int dir);
    void intersection(int problem);
    bool backtrack(int dir);
    
};

#include "game.cpp"

#endif

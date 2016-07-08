 #include <iterator>
#include <stdlib.h>
#include <vector>
#include <ostream>
#include <algorithm>
using namespace std;

#include "list.h"

Game::Game(int n){
    
    grid = new char[n*n];
    
    for (int i = 0; i < n*n; i++) {
        grid[i] = '.';
    }
    
    grid[(n/2)*n + (n/2)] = 'r';
    grid[0] = 'R';
    
    green = List<int>();
    red = List<int>();
    
    red.insertFront(0);
    headx = 0;
    heady = 0;
}

Game::Game( const Game & other ){
    copy(other);
}

Game & Game::operator=( const Game & rhs ){
    
    delete[] grid;
    copy(rhs);
    return *this;
}

Game::~Game(){
    delete[] grid;
}

void Game::move(int dir){
    
    if (dir != 0 && dir != 1 && dir != 2 && dir != 3) {
        if (redalive && score() > 5) {
            green = red.split();
            green.reverse();
            int temp;
            for (int i=0; i<green.size(); i++) {
                temp = green.popBack();
                changes.insertFront(temp);
                grid[temp] = 'G';
            }
        }
    }
    
    // if backtrack
    if (backtrack(dir)) {
        if (redalive) {
            red.reverse();
        } else {
            green.reverse();
        }
    }
    
    int next = nextTile(dir);
    
    // if hit apple of same color
    
    if (grid[next] == 'r' && redalive) {
        red.insertFront(next);
        grid[next] = 'R';
        changes.insertFront(next);
        nextApple();
        return;
    }
    if (grid[next] == 'g' && !redalive) {
        green.insertFront(next);
        grid[next] = 'G';
        changes.insertFront(next);
        nextApple();
        return;
    }
    
    // if hit apple of different color
    
    // Green into Red Apple
    if (grid[next] == 'r' && !redalive) {
        green.insertFront(next);
        int end = green.popBack();
        grid[end] = '.';
        grid[next] = 'G';
        nextApple();
        changes.insertFront(end);
        changes.insertFront(next);
        return;
    }
    
    // Red into Green apple
    if (grid[next] == 'g' && redalive) {
        green = red.split();
        green.reverse();
        int temp;
        for (int i=0; i<green.size(); i++) {
            temp = green.popBack();
            changes.insertFront(temp);
            grid[temp] = 'G';
        }
    }
    
    // Collide
    if (grid[next] == 'G' || grid[next] == 'R') {
        intersection(next);
        return;
    }
    
    // Just walking, nothing to see here
    
    if (redalive) {
        
        int end = red.popBack();
        grid[end] = '.';
        grid[next] = 'R';
        red.insertFront(next);
        changes.insertFront(end);
        changes.insertFront(next);
        
    } else {
        
        int end = green.popBack();
        grid[end] = '.';
        grid[next] = 'G';
        green.insertFront(next);
        changes.insertFront(end);
        changes.insertFront(next);
        
    }
    
}

int Game::score(){
    
    if (redalive) {return red.size();}
    else {return green.size();}
    
}

void Game::print() const{
    for (int i = 0; i < side; i++)
    {
        for (int j = 0; j < side; j++)
        {
            cout << grid[(i*side) + j] << ' ';
        }
        cout << endl;
    }
    
}

void Game::copy(const Game & other) {
    
    grid = new char[other.side*other.side];
    for (int i = 0; i < other.side*other.side; i++) {
        grid[i] = other.grid[i];
    }
    
    red = other.red;
    green = other.green;
    changes = other.changes;
    headx = other.headx;
    heady = other.heady;
    redalive = other.redalive;
    side = other.side;
}

int Game::nextTile(int dir) {
    
    // HERE'S MY NUMBER, SO CALL ME MAYBE.
    int x;
    int y;
    int loc;
    
    if (redalive) {
        red.reverse();
        int temp = red.popBack();
        red.reverse();
        red.insertFront(temp);
        loc = temp;
    } else {
        green.reverse();
        int temp = green.popBack();
        green.reverse();
        green.insertFront(temp);
        loc = temp;
    }
    
    x = loc % side;
    y = (loc - x)/side;
    
    if (dir == 0) { // DOWN
        y++;
        if (y > 2) {
            y--;
            if (x-1 > 0) x--;
            else x++;
        }
    }
    else if (dir == 1) { // LEFT
        x--;
        if (x < 0) {
            x++;
            if (y-1 > 0) y--;
            else y++;
        }
    }
    else if (dir == 2) { // RIGHT
        x++;
        if (x > 2) {
            x--;
            if (y-1 > 0) y--;
            else y++;
        }
    }
    else { // UP
        y--;
        if (y < 0) {
            y++;
            if (x-1 > 0) x--;
            else x++;
        }
    }
    
    headx = x;
    heady = y;
    return (y * side + x);
    
}

void Game::nextApple() {
    
    int r = 0;
    
    while (grid[r] != '.') {
        r  = rand() % side * side;
    }
    
    int r2 = rand() % 2 + 1; // 1 or 2
    
    if (red.size() > 5 && r2 != 1) {grid[r] = 'g';}
    else {grid[r] = 'r';}
    changes.insertFront(r);
    
}

void Game::intersection(int problem) {
    
    if (redalive) {
        
        int temp = red.popBack();
        changes.insertFront(temp);
        grid[temp] = '.';
        while (temp != problem) {
            temp = red.popBack();
            changes.insertFront(temp);
            grid[temp] = '.';
        }
        
    } else {
        
        if (grid[problem] == 'G') {
            
            int temp = green.popBack();
            changes.insertFront(temp);
            grid[temp] = '.';
            while (temp != problem) {
                temp = green.popBack();
                changes.insertFront(temp);
                grid[temp] = '.';
            }
            
        } else {
            
            redalive = true;
            
            // pop red
            int temp = red.popBack();
            grid[temp] = '.';
            changes.insertFront(temp);
            while (temp != problem) {
                temp = red.popBack();
                changes.insertFront(temp);
                grid[temp] = '.';
            }
            
            //update changes
            int zoo;
            for (int i=0; i < green.size(); i++) {
                zoo = green.popBack();
                changes.insertFront(zoo);
                changes.insertFront(zoo);
            }
            
            // insert problem
            green.insertFront(problem);
            grid[problem] = 'G';
            
            // merge
            red.mergeWith(green);
            
            //update grid
            int foo;
            for (int i=0; i < red.size(); i++) {
                foo = red.popBack();
                grid[foo] = 'R';
                red.insertFront(foo);
            }
            
        }
    }
}

bool Game::backtrack(int dir) {
    
    int next = nextTile(dir);
    
    if (red.size() < 2) {return true;}
    
    int secondFront;
    // getting the second to front
    for (int i=0; i<red.size(); i++) {
        int temp = red.popBack();
        if (i == red.size()-2) {secondFront = temp;}
        red.insertFront(temp);
    }
    
    if (redalive) {
        
        if (grid[next] == secondFront) {return true;}
        else return false;
        
    } else {
        
        if (grid[next] == secondFront) {return true;}
        else return false;
    }
    
}


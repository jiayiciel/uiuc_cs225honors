#include "list.h"
#include "game.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
#include <SFML/Graphics.hpp>

int main()
{
   sf::RenderWindow window(sf::VideoMode(400, 400), "CS225 MP3 Snake Game");
   Game g(20);
   window.clear();

   while (window.isOpen())
   {
      sf::Event event;
      while (window.pollEvent(event))
      {
         if (event.type == sf::Event::Closed)
            window.close();
      }

      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
      {
         while (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {}
         g.move(1);
      }

      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
      {
         while (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {}
         g.move(2);
      }

      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
      {
         while (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {}
         g.move(3);
      }

      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
      {
         while (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {}
         g.move(0);
      }

      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
      {
         while (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {}
         g.move(4);
      }
      //window.clear();
      sf::CircleShape circle(10);
      while(!(g.changes.empty()))
      {
         int curr = g.changes.popBack();
            if (g.grid[curr] == 'r' || g.grid[curr] == 'R')
            {
               circle.setFillColor(sf::Color::Red);
               circle.setPosition((curr%20)*20, (curr/20)*20);
               window.draw(circle);
            } 

            if (g.grid[curr] == 'g' || g.grid[curr] == 'G')
            {
               circle.setFillColor(sf::Color::Green);
               circle.setPosition((curr%20)*20, (curr/20)*20);
               window.draw(circle);
            }

            if (g.grid[curr] == '.')
            {
               circle.setFillColor(sf::Color::Black);
               circle.setPosition((curr%20)*20, (curr/20)*20);
               window.draw(circle);
            }
      }
        
      window.display();
    }
    cout<< "Final Score is " << g.score() << endl;
    return 0;
}


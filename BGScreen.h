#ifndef BGScreen_SCREEN_H
#define BGScreen_SCREEN_H

#include <SFML/Graphics.hpp>

#include "Game.h"

namespace sfSnake
{
    class BGScreen
    {
    public:
        BGScreen();
        void drawCell(sf::RenderWindow &window); 
        void drawBG(sf::RenderWindow &window); 
        bool getifcell();
        int getchoosebg();
        void changeifcell(bool t);
        void changechoosebg(int t);

        bool ifcell_;
        int choosebg_;
    private:
        sf::Sprite sprbg_;  
    };
}

#endif
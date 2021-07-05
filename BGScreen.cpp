#include <SFML/Graphics.hpp>

#include "BGScreen.h"
#include "Game.h"

using namespace sfSnake;

BGScreen::BGScreen() : choosebg_(1), ifcell_(1)
{
    
}

void BGScreen::drawBG(sf::RenderWindow &window)
{
    if(getchoosebg()==1)
    {
        static sf::Texture texbg_;
        texbg_.loadFromFile("Backgrounds/BG2.jpg");
        // texbg_.setRepeated(true);
        sprbg_.setTexture(texbg_);
        sprbg_.setTextureRect(sf::IntRect(0,0,Game::Width,Game::Height));
        window.draw(sprbg_);
    }
    else if(getchoosebg()==2)//黑屏
    {
        
    }
    else if(getchoosebg()==3)//白屏
    {
        sf::RectangleShape Recbg(sf::Vector2f(1280, 960));
        Recbg.setFillColor(sf::Color::White);
        window.draw(Recbg);
    }
}

void BGScreen::drawCell(sf::RenderWindow &window)
{
    if(getifcell()==1)
    {
        for(int i=50;i<=960;i+=50)
        {
            sf::RectangleShape line(sf::Vector2f(1280, 1));
            line.setPosition(sf::Vector2f(0,i));
            line.setFillColor(sf::Color(119,136,153));
            window.draw(line);
        }
        for(int i=50;i<=1280;i+=50)
        {
            sf::RectangleShape line(sf::Vector2f(960, 1));
            line.setPosition(sf::Vector2f(i,0));
            line.setFillColor(sf::Color(119,136,153));
            line.rotate(90);
            window.draw(line);
        }
    }
    return ;
}
bool BGScreen::getifcell()
{
    return ifcell_;
}
int BGScreen::getchoosebg()
{
    return choosebg_;
}
void BGScreen::changeifcell(bool t)
{
    ifcell_=t;
}
void BGScreen::changechoosebg(int t)
{
    choosebg_=t;
}
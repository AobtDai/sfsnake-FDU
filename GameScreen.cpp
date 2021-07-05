#include <SFML/Graphics.hpp>

#include <random>
#include <memory>

#include "GameScreen.h"
#include "GameOverScreen.h"
#include "Game.h"

using namespace sfSnake;

int Fruitnum=100;
GameScreen::GameScreen() : snake_()
{

}

void GameScreen::handleInput(sf::RenderWindow& window)
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		back_ground_.changeifcell(1-back_ground_.getifcell());
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
	{
		back_ground_.changechoosebg(1);
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
	{
		back_ground_.changechoosebg(2);
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
	{
		back_ground_.changechoosebg(3);
	}
	
	snake_.handleInput(window);
}

void GameScreen::update(sf::Time delta)
{
	int fsize=static_cast<int>(fruit_.size());
	int colornum=0;

	snake_.update(delta);
	colornum=snake_.checkFruitCollisions(fruit_);

	if (fsize < Fruitnum)
		generateFruit(fsize, colornum);

	if (snake_.hitSelf())
		Game::Screen = std::make_shared<GameOverScreen>(snake_.getSize());
}

void GameScreen::render(sf::RenderWindow& window)
{
	back_ground_.drawBG(window);
	back_ground_.drawCell(window);
	snake_.render(window);

	for (auto fruit : fruit_)
		fruit.render(window);
}

void GameScreen::generateFruit(int nownum, int colornum)	// 随机数引擎
{
	std::random_device sd;
	static std::default_random_engine engine;
	engine.seed(sd()*time(NULL));
	static std::uniform_int_distribution<int> xDistribution(0, Game::Width - SnakeNode::Width);
	static std::uniform_int_distribution<int> yDistribution(0, Game::Height - SnakeNode::Height);
	static std::uniform_int_distribution<int> color_num(1, 32555);

	if(nownum==0)
	{		
		for(int i=nownum; i<=Fruitnum/4; i++)
			fruit_.push_back(Fruit(sf::Vector2f(xDistribution(engine), yDistribution(engine)), color_num(engine)%2+1));
		for(int i=Fruitnum/4+1; i<=Fruitnum; i++)
			fruit_.push_back(Fruit(sf::Vector2f(xDistribution(engine), yDistribution(engine)), color_num(engine)%3+3));
	}
	else if(colornum>0)
		fruit_.push_back(Fruit(sf::Vector2f(xDistribution(engine), yDistribution(engine)), colornum));
	
}

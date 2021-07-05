#include <SFML/Graphics.hpp>

#include "Fruit.h"

using namespace sfSnake;

const float Fruit::Radius = 6.f;

// 1-black 2-brown 3-red 4-blue 5-green
Fruit::Fruit(sf::Vector2f position, int colornum)
{
	shape_.setPosition(position);
	shape_.setRadius(Fruit::Radius);
	Fruit::colornum_=colornum;
	switch(colornum)
	{
		case 1:
			shape_.setFillColor(sf::Color::Black);	// 暂时改变颜色
			Fruit::add_l=0;
			break;
		case 2:	
			shape_.setFillColor(sf::Color(160, 82, 45));
			Fruit::add_l=0;
			break;
		case 3:	
			shape_.setFillColor(sf::Color::Red);
			Fruit::add_l=3;
			break;
		case 4:
			shape_.setFillColor(sf::Color::Blue);
			Fruit::add_l=2;
			break;
		case 5:	
			shape_.setFillColor(sf::Color::Green);
			Fruit::add_l=1;
			break;
	}
}

void Fruit::render(sf::RenderWindow &window)
{
	window.draw(shape_);
}

sf::FloatRect Fruit::getBounds() const
{
	return shape_.getGlobalBounds();
}

int Fruit::getColornum() const
{
	return colornum_;
}

int Fruit::getaddl() const
{
	return add_l;
}
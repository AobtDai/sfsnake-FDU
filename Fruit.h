#ifndef FRUIT_H
#define FRUIT_H

#include <SFML/Graphics.hpp>

namespace sfSnake
{
	class Fruit
	{
	public:
		Fruit(sf::Vector2f position = sf::Vector2f(0, 0), int colornum=3);
		void render(sf::RenderWindow &window);
		sf::FloatRect getBounds() const;
		int getColornum() const;
		int getaddl() const;

	private:
		sf::CircleShape shape_;
		static const float Radius;
		int colornum_, add_l;
	};
}

#endif
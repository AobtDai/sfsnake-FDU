#ifndef SNAKE_NODE_H
#define SNAKE_NODE_H

#include <SFML/Graphics.hpp>

namespace sfSnake
{
	class SnakeNode
	{
	public:
		SnakeNode(sf::Vector2f position = sf::Vector2f(0, 0), int ifhead = 0);

		void setPosition(sf::Vector2f position);
		void setPosition(float x, float y);

		void move(float xOffset, float yOffset);

		void render(sf::RenderWindow &window);

		sf::Vector2f getPosition() const;
		sf::FloatRect getBounds() const;
		bool getIfhead() const;

		static const float Width;
		static const float Height;

	private:
		sf::Vector2f position_;

		sf::Sprite spr_;
		sf::Sprite sprbody_;
		bool if_head_;
	};
}

#endif
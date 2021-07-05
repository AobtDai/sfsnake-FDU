#ifndef SNAKE_H
#define SNAKE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <vector>

#include "SnakeNode.h"
#include "Fruit.h"

namespace sfSnake
{
	enum class Direction
	{
		Left, Right, Up, Down, Mouse_Vec
	};

class Snake
{
public:
	Snake();

	void handleInput(sf::RenderWindow& window);
	void update(sf::Time delta);
	void render(sf::RenderWindow& window);

	int checkFruitCollisions(std::vector<Fruit>& fruits);

	bool hitSelf() const;
	double dis(sf::Vector2f p1, sf::Vector2f p2) const;

	unsigned getSize() const;

private:
	void move();
	void grow(int add_l);
	void checkEdgeCollisions();
	void checkSelfCollisions();
	void initNodes();

	bool hitSelf_;

	sf::Vector2f position_;
	sf::Vector2f mouse_diriction_;
	Direction direction_;

	sf::SoundBuffer pickupBuffer_;
	sf::Sound pickupSound_;

	sf::SoundBuffer dieBuffer_;
	sf::Sound dieSound_;

	std::vector<SnakeNode> nodes_;

	static const int InitialSize;
};
}

#endif
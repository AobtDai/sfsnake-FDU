#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H

#include <SFML/Graphics.hpp>

#include "Screen.h"
#include "Snake.h"
#include "Fruit.h"
#include "BGScreen.h"

namespace sfSnake
{
	class GameScreen : public Screen
	{
	public:
		GameScreen();

		void handleInput(sf::RenderWindow &window) override;
		void update(sf::Time delta) override;
		void render(sf::RenderWindow &window) override;

		void generateFruit(int nownum, int colornum);

		BGScreen back_ground_;

	private:
		Snake snake_;
		std::vector<Fruit> fruit_;
	};
}

#endif
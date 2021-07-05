#include <SFML/Graphics.hpp>

#include <memory>
#include <iostream>
#include <cmath>

#include "Snake.h"
#include "Game.h"
#include "Fruit.h"
#include "SnakeNode.h"
#include "GameOverScreen.h"
#include "GameScreen.h"

using namespace sfSnake;

const int Snake::InitialSize = 5;	// 初始长度
const double Prop=1;

// 以下方向控制部分要改
// 以下为各元素的初始化
Snake::Snake() : direction_(Direction::Up), hitSelf_(false)
{
	initNodes();

	pickupBuffer_.loadFromFile("Sounds/pickup.aiff");
	pickupSound_.setBuffer(pickupBuffer_);
	pickupSound_.setVolume(30);

	dieBuffer_.loadFromFile("Sounds/die.wav");
	dieSound_.setBuffer(dieBuffer_);
	dieSound_.setVolume(50);
}

void Snake::initNodes()
{
	nodes_.push_back(SnakeNode(sf::Vector2f(
			Game::Width / 2 - SnakeNode::Width / 2,
			Game::Height / 2 - (SnakeNode::Height / 2) + (SnakeNode::Height)), 1));
	for (int i = 1; i < Snake::InitialSize; ++i)
	{
		nodes_.push_back(SnakeNode(sf::Vector2f(
			Game::Width / 2 - SnakeNode::Width / 2,
			Game::Height / 2 - (SnakeNode::Height / 2) + (SnakeNode::Height * i * Prop)), 0));
	}
}

// 此部分为方向控制，需要改成鼠标控制
void Snake::handleInput(sf::RenderWindow& window)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		direction_ = Direction::Up;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		direction_ = Direction::Down;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		direction_ = Direction::Left;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		direction_ = Direction::Right;
	else if(sf::Mouse::isButtonPressed(sf::Mouse::Left))//鼠标控制-方向处理
    {
        direction_ = Direction::Mouse_Vec;
        sf::Vector2f head_pos = nodes_[0].getPosition();
        sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
		double deno=sqrt((mouse_pos.x-head_pos.x)*(mouse_pos.x-head_pos.x)+(mouse_pos.y-head_pos.y)*(mouse_pos.y-head_pos.y));
        mouse_diriction_=SnakeNode::Height*sf::Vector2f((mouse_pos.x-head_pos.x)/deno,(mouse_pos.y-head_pos.y)/deno);
    }

	/*if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		GameScreen::back_ground_.changeifcell(1-GameScreen::back_ground_.getifcell());
	}*/
} 

void Snake::update(sf::Time delta)
{
	move();
	checkEdgeCollisions();
	checkSelfCollisions();
}

int Snake::checkFruitCollisions(std::vector<Fruit>& fruits)
{
	int colornum=0;
	decltype(fruits.begin()) toRemove = fruits.end();

	for (auto it = fruits.begin(); it != fruits.end(); ++it)//这里删除&
	{
		if (it->getBounds().intersects(nodes_[0].getBounds()))
			toRemove = it;
	}

	if (toRemove != fruits.end())
	{
		pickupSound_.play();
		grow(toRemove->getaddl());
		colornum=toRemove->getColornum();
		fruits.erase(toRemove);
	}
	return colornum;
}

void Snake::grow(int add_l)
{
	for(auto i=1; i<=add_l; i++)
	{
		switch (direction_)
		{
		case Direction::Up:
			nodes_.push_back(SnakeNode(sf::Vector2f(nodes_[nodes_.size() - 1].getPosition().x,
				nodes_[nodes_.size() - 1].getPosition().y + SnakeNode::Height*Prop)));
			break;
		case Direction::Down:
			nodes_.push_back(SnakeNode(sf::Vector2f(nodes_[nodes_.size() - 1].getPosition().x,
				nodes_[nodes_.size() - 1].getPosition().y - SnakeNode::Height*Prop)));
			break;
		case Direction::Left:
			nodes_.push_back(SnakeNode(sf::Vector2f(nodes_[nodes_.size() - 1].getPosition().x + SnakeNode::Width*Prop,
				nodes_[nodes_.size() - 1].getPosition().y)));
			break;
		case Direction::Right:
			nodes_.push_back(SnakeNode(sf::Vector2f(nodes_[nodes_.size() - 1].getPosition().x - SnakeNode::Width*Prop,
				nodes_[nodes_.size() - 1].getPosition().y)));
			break;
		}
	}
}

unsigned Snake::getSize() const
{
	return nodes_.size();
}

bool Snake::hitSelf() const
{
	return hitSelf_;
}

double Snake::dis(sf::Vector2f p1, sf::Vector2f p2) const
{
	return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
}

void Snake::checkSelfCollisions()
{
	SnakeNode& headNode = nodes_[0];

	for (decltype(nodes_.size()) i = 1; i < nodes_.size(); ++i)
	{
		if (dis(nodes_[0].getPosition(),nodes_[i].getPosition())<SnakeNode::Height/2)// difference
		{
			dieSound_.play();
			sf::sleep(sf::seconds(dieBuffer_.getDuration().asSeconds()));//？？？
			hitSelf_ = true;
		}
	}
}

void Snake::checkEdgeCollisions()
{
	SnakeNode& headNode = nodes_[0];

	if (headNode.getPosition().x <= 0)
		headNode.setPosition(Game::Width, headNode.getPosition().y);
	else if (headNode.getPosition().x >= Game::Width)
		headNode.setPosition(0, headNode.getPosition().y);
	else if (headNode.getPosition().y <= 0)
		headNode.setPosition(headNode.getPosition().x, Game::Height);
	else if (headNode.getPosition().y >= Game::Height)
		headNode.setPosition(headNode.getPosition().x, 0);
}

void Snake::move()
{
	for (decltype(nodes_.size()) i = nodes_.size() - 1; i > 0; --i)
	{
		nodes_[i].setPosition(nodes_.at(i - 1).getPosition());
	}

	switch (direction_)
	{
	case Direction::Up:
		nodes_[0].move(0, -SnakeNode::Height*Prop);
		break;
	case Direction::Down:
		nodes_[0].move(0, SnakeNode::Height*Prop);
		break;
	case Direction::Left:
		nodes_[0].move(-SnakeNode::Width*Prop, 0);
		break;
	case Direction::Right:
		nodes_[0].move(SnakeNode::Width*Prop, 0);
		break;
	case Direction::Mouse_Vec://如果刚刚是鼠标点击，则朝着对应方向前进
        nodes_[0].move(mouse_diriction_.x,mouse_diriction_.y);
        break;
	}
}

void Snake::render(sf::RenderWindow& window)
{
	for (auto node : nodes_)
		node.render(window);
}
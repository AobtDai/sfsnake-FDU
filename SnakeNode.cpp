#include <SFML/Graphics.hpp>
#include <iostream>

#include "SnakeNode.h"

using namespace sfSnake;

const float SnakeNode::Width = 30.f;
const float SnakeNode::Height = 30.f;

SnakeNode::SnakeNode(sf::Vector2f position, int ifhead)	//蛇样式初始化
	: position_(position), if_head_(ifhead)
{
	static sf::Texture tex_;
	tex_.loadFromFile("Nodes/head0.png");
    spr_.setTexture(tex_, true );
    spr_.setTextureRect(sf::IntRect(0,0,30,30));
    spr_.setPosition(position_);
    spr_.setOrigin(sf::Vector2f(15,15));


	static sf::Texture texbody_;
	texbody_.loadFromFile("Nodes/snakenode.png");
    sprbody_.setTexture(texbody_, true );
    sprbody_.setTextureRect(sf::IntRect(0,0,30,30));
    sprbody_.setPosition(position_);
    sprbody_.setOrigin(sf::Vector2f(15,15));
	sprbody_.setScale(sf::Vector2f(0.8,0.8));
}

void SnakeNode::setPosition(sf::Vector2f position)
{
	position_ = position;
	spr_.setPosition(position_);
	sprbody_.setPosition(position_);
}

void SnakeNode::setPosition(float x, float y)
{
	position_.x = x;
	position_.y = y;
	spr_.setPosition(position_);
	sprbody_.setPosition(position_);
}

void SnakeNode::move(float xOffset, float yOffset)
{
	position_.x += xOffset;
	position_.y += yOffset;
	spr_.setPosition(position_);
	sprbody_.setPosition(position_);
}

sf::FloatRect SnakeNode::getBounds() const
{
	if(if_head_) return spr_.getGlobalBounds();
	else return sprbody_.getGlobalBounds();
}

sf::Vector2f SnakeNode::getPosition() const
{
	return position_;
}

bool SnakeNode::getIfhead() const
{
	return if_head_;
}

void SnakeNode::render(sf::RenderWindow &window)
{
	if(if_head_) window.draw(spr_);
	else window.draw(sprbody_);
}
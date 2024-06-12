#include "Wall.h"
#include<cmath>

Wall::Wall(sf::Vector2f position, float size)
{
	this->setPosition(position);
	this->setSize(sf::Vector2f(size, size));
}

int Wall::collide(Ball& ball)
{
	//test collision
	float testX = ball.getPosition().x;
	float testY = ball.getPosition().y;
	if (ball.getPosition().x < this->getPosition().x)
	{
		testX = this->getPosition().x; // test left edge
	}
	else if (ball.getPosition().x > this->getPosition().x + this->getSize().x)
	{
		testX = this->getPosition().x + this->getSize().x; // right edge
	}

	if (ball.getPosition().y < this->getPosition().y)
	{
		testY = this->getPosition().y; // top edge
	}
	else if (ball.getPosition().y > this->getPosition().y + this->getSize().y)
	{
		testY = this->getPosition().y + this->getSize().y; // bottom edge
	}

	float distX = ball.getPosition().x - testX;
	float distY = ball.getPosition().y - testY;
	float distance = std::sqrt((distX * distX) + (distY * distY));
	
	//make collision
	bool collision = false;
	if (distance <= ball.getRadius())
	{
		if (testX == this->getPosition().x && distX < 0) // Left side
		{
			collision = true;
			ball.setDirection(sf::Vector2f( - std::abs(ball.getDirection().x), ball.getDirection().y));
		}
		else if (testX == this->getPosition().x + this->getSize().x && distX > 0) // Right side
		{
			collision = true;
			ball.setDirection(sf::Vector2f(std::abs(ball.getDirection().x), ball.getDirection().y));
		}

		if (testY == this->getPosition().y && distY < 0) // Top side
		{
			collision = true;
			ball.setDirection(sf::Vector2f(ball.getDirection().x, -std::abs(ball.getDirection().y)));
		}
		else if (testY == this->getPosition().y + this->getSize().y && distY > 0) // Bottom side
		{
			collision = true;
			ball.setDirection(sf::Vector2f(ball.getDirection().x, std::abs(ball.getDirection().y)));
		}
	}

	if (collision)
	{
		return 2;
	}
	else
	{
		return -1;
	}
}
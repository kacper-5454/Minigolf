#include "Hole.h"
#include<iostream>

Hole::Hole(sf::Vector2f position, float size)
{
	this->setPosition(position);
	this->setSize(sf::Vector2f(size, size));
}

int Hole::collide(Ball& ball)
{
	sf::FloatRect hole_bounds = this->getGlobalBounds();
	if (hole_bounds.contains(ball.getPosition()))
	{
		if(ball.getSpeed() < 150.0)
		{
			return 3;
		}
		else
		{
			ball.setFriction(50.0);
		}	
	}
	return -1;
}
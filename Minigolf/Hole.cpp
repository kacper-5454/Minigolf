#include "Hole.h"
#include<iostream>

Hole::Hole(sf::Vector2f position, float size)
{
	this->setPosition(position);
	this->setSize(sf::Vector2f(size, size));
}

void Hole::collide(Ball& ball)
{
	sf::FloatRect hole_bounds = this->getGlobalBounds();
	if (hole_bounds.contains(ball.getPosition()))
	{
		if(ball.getSpeed() < 100.0)
		{
			std::cout << "Level won, make apropriate screen" << std::endl;
		}
		else
		{
			ball.setFriction(50.0);
		}	
	}
}
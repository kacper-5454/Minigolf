#include "Water.h"

Water::Water(sf::Vector2f position, float size)
{
	this->setPosition(position);
	this->setSize(sf::Vector2f(size, size));
}

void Water::collide(Ball& ball)
{
	sf::FloatRect water_bounds = this->getGlobalBounds();
	if (water_bounds.contains(ball.getPosition()))
	{
		//revert to last move
	}
}

#include "Sand.h"

Sand::Sand(sf::Vector2f position, float size)
{
	this->setPosition(position);
	this->setSize(sf::Vector2f(size, size));
}

void Sand::collide(Ball& ball)
{
	sf::FloatRect sand_bounds = this->getGlobalBounds();
	if (sand_bounds.contains(ball.getPosition()))
	{
		ball.setFriction(700.0);
	}
}

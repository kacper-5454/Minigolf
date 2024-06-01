#include "Grass.h"

Grass::Grass(sf::Vector2f position, float size)
{
	this->setPosition(position);
	this->setSize(sf::Vector2f(size, size));
}

bool Grass::collide(Ball& ball)
{
	sf::FloatRect sand_bounds = this->getGlobalBounds();
	if (sand_bounds.contains(ball.getPosition()))
	{
		ball.setFriction(50.0);
	}
	return false;
}

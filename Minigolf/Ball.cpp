#include "Ball.h"
Ball::Ball(std::string texture_name, sf::Vector2f initial_position)
{
    if (!texture.loadFromFile(texture_name))
    {
        throw("Wrong texture filename");
        this->setFillColor(sf::Color::White);
    }
    this->setTexture(&texture);
    this->setRadius(5.0);
	this->setPosition(initial_position);
}

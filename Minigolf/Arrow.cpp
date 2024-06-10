#include "Arrow.h"
#include<cmath>
#include<iostream>

const float pi = 3.14159265358979323846;

void Arrow::setArrowTexture(sf::Texture* tex)
{
	this->texture = tex;
	this->setTexture(*this->texture);
	this->setOrigin(0.0, this->getLocalBounds().height / 2.0);
}

void Arrow::update(sf::Vector2f ball_position, sf::Vector2f direction, float speed, float ball_radius)
{
	float force_factor = speed / 2000.0;
	this->setScale(force_factor, 0.25);

	float angle = atan2(direction.y, direction.x);
	this->setRotation(angle*180.0 / pi);
	
	sf::Vector2f pos;
	pos.x = ball_position.x + ball_radius * (cos(angle) + 1);
	pos.y = ball_position.y + ball_radius * (sin(angle) + 1);
	this->setPosition(pos);
}

void Arrow::draw(sf::RenderWindow& window)
{
	window.draw(*this);
}

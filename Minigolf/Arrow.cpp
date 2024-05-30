#include "Arrow.h"
#include<cmath>
#include<iostream>

const float pi = 3.14159265358979323846;

Arrow::Arrow()
{
	this->rectangle.setSize(sf::Vector2f(0.0, 0.0));
	this->rectangle.setFillColor(sf::Color(255, 49, 49));
	this->rectangle.setOutlineColor(sf::Color(130, 6, 0));
	this->rectangle.setOutlineThickness(1.0);

	this->triangle.setFillColor(sf::Color(255, 49, 49));
	this->triangle.setOutlineThickness(1.0);
	this->triangle.setOutlineColor(sf::Color(130, 6, 0));

	this->triangle.setPointCount(3);
	this->triangle.setPoint(0, sf::Vector2f(0, -this->triangle_height / 2)); // top point
	this->triangle.setPoint(1, sf::Vector2f(-this->triangle_base / 2, this->triangle_height / 2)); // bottom left point
	this->triangle.setPoint(2, sf::Vector2f(this->triangle_base / 2, this->triangle_height / 2)); // bottom right point
}
void Arrow::update(sf::Vector2f ball_position, sf::Vector2f direction, float speed, float ball_radius)
{
	float force_factor = speed / 10.0;
	sf::Vector2f rect_size(1.0 * force_factor, 5.0);
	this->rectangle.setSize(rect_size);
	this->rectangle.setOrigin(sf::Vector2f(rect_size.x/2, rect_size.y/2));

	float angle =  atan2(direction.y, direction.x);

	this->rectangle.setRotation(angle*180.0 / pi);
	sf::Vector2f rectangle_pos;
	rectangle_pos.x = ball_position.x + direction.x * (ball_radius + rect_size.y / 2);
	rectangle_pos.y = ball_position.y + direction.y * (ball_radius + rect_size.y / 2);
	this->rectangle.setPosition(rectangle_pos);
	
	// Position the triangle at the end of the rectangle
	sf::Vector2f triangle_pos;
	triangle_pos.x = rectangle_pos.x + direction.x * (rect_size.y / 2 + triangle_height / 2);
	triangle_pos.y = rectangle_pos.y + direction.y * (rect_size.y / 2 + triangle_height / 2);
	this->triangle.setPosition(triangle_pos);

	// Rotate the triangle to match the rectangle's direction
	this->triangle.setRotation(angle * 180.0 / pi);
}

void Arrow::draw(sf::RenderWindow& window)
{
	window.draw(this->rectangle);
	//window.draw(this->triangle);
}

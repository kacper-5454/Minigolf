#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
class Arrow
{
private:
	sf::RectangleShape rectangle;
	sf::ConvexShape triangle;
	float triangle_height = 9.0;
	float triangle_base = 7.5;
public:
	Arrow();
	void update(sf::Vector2f, sf::Vector2f, float, float);
	void draw(sf::RenderWindow&);
};


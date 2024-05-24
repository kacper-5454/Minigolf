#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
class Screen : public sf::RectangleShape
{
public:
	virtual ~Screen() = default;
	virtual char run(sf::RenderWindow& window) = 0;
};


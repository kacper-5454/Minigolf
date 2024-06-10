#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include"BackgroundElement.h"
class Wall : public BackgroundElement
{
public:
	Wall(sf::Vector2f, float);
	int collide(Ball&);
};


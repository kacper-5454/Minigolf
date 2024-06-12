#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include"BackgroundElement.h"

class Water : public BackgroundElement
{
public:
	Water(sf::Vector2f, float);
	int collide(Ball&);
};


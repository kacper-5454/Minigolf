#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include"BackgroundElement.h"
class Hole : public BackgroundElement
{
public:
	Hole(sf::Vector2f, float);
	int collide(Ball&);
};


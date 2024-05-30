#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include"BackgroundElement.h"
class Sand : public BackgroundElement
{
public:
	Sand(sf::Vector2f, float);
	void collide(Ball&);
};


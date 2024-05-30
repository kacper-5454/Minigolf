#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include"Ball.h"
class BackgroundElement : public sf::RectangleShape
{
public:
	virtual void collide(Ball&) = 0;
};


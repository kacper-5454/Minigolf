#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include"Ball.h"

class BackgroundElement : public sf::RectangleShape
{
public:
	virtual int collide(Ball&) = 0;
};


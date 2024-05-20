#pragma once
#include"Background.h"
class Grass : public Background
{
private:
	float friction = 0.25;
public:
	Grass(sf::Vector2f);
};

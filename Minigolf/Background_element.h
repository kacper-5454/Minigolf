#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include"Background_type.h"

class Background_element : public sf::RectangleShape
{
private:
	Background_type type;
public:
	Background_element(Background_type, sf::Vector2f, float size);
	Background_type getType();
};


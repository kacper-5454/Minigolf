#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Screen : public sf::RectangleShape
{
protected:
	sf::Font font;
public:
	virtual ~Screen() = default;
	virtual std::string run(sf::RenderWindow& window) = 0;
	sf::Texture loadTexture(std::string);
};


#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
class Button : sf::RectangleShape
{
private:
	sf::Texture texture;
public:
	Button(std::string, sf::Vector2f);
	Button();
	void draw(sf::RenderWindow&);
	bool isClicked(sf::Vector2i);
};


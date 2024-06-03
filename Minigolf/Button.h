#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
class Button : sf::RectangleShape
{
private:
	sf::Texture texture;
	sf::Font font;
	sf::Text text;
public:
	Button(std::string, sf::Vector2f, sf::Vector2f);
	Button();
	void draw(sf::RenderWindow&);
	bool isClicked(sf::Vector2f);
};


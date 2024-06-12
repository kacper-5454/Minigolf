#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Textbox : public sf::RectangleShape
{
private:
	sf::Font font;
	sf::Text text;
	std::string text_string;
public:
	Textbox(sf::Vector2f, sf::Vector2f, sf::RenderWindow&);
	void setupText(sf::Vector2f, sf::RenderWindow&);
	void draw(sf::RenderWindow&);
	void appendString(char);
	std::string getString();
	void backspace();
};


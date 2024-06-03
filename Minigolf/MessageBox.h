#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include"Button.h"
class MessageBox : sf::RectangleShape
{
private:
	sf::Texture texture;
	sf::Font font;
	sf::Text text;
	Button button;
public:
	MessageBox(std::string, std::string, int, int);
	void draw_message(sf::RenderWindow&);
	bool run(sf::RenderWindow&);
};


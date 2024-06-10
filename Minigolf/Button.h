#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
class Button : sf::RectangleShape
{
private:
	sf::Texture texture;
	sf::Font font;
	sf::Text text;
	sf::Sound sound;
	sf::SoundBuffer buffer;
public:
	Button(std::string, sf::Vector2f, sf::Vector2f);
	Button() = default;
	void draw(sf::RenderWindow&);
	bool isClicked(sf::Vector2f);
};


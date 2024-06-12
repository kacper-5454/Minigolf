#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include<SFML/Audio.hpp>

class BackArrow : public sf::RectangleShape
{
private:
	sf::Texture texture;
	sf::SoundBuffer buffer;
	sf::Sound sound;
public:
	BackArrow(sf::Vector2f, sf::RenderWindow&);
	bool isClicked(sf::Vector2f);
};


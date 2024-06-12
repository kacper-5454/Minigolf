#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include"Button.h"
#include"Screen.h"

class TitleScreen : public Screen
{
private:
	sf::Texture texture;
	Button play_button;
	Button create_button;
	sf::Text title;
	sf::SoundBuffer buffer;
	sf::Sound sound;
public:
	TitleScreen(sf::RenderWindow&);
	std::string run(sf::RenderWindow&);
	void draw(sf::RenderWindow&);
	char detectButton(sf::Vector2f);
	void makeTitle(sf::RenderWindow&);
};


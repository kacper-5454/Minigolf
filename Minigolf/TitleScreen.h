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
	Button play_button = Button("PLAY", sf::Vector2f(220.0, 270.0), sf::Vector2f(120.0, 60.0));
	Button create_button = Button("CREATE", sf::Vector2f(460.0, 270.0), sf::Vector2f(120.0, 60.0));
	sf::Font font;
	sf::Text title;
	sf::Music music;
public:
	TitleScreen(int, int);
	std::string run(sf::RenderWindow&);
	void draw(sf::RenderWindow&);
	char detectButton(sf::Vector2f);
};


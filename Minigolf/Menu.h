#pragma once
#include "Screen.h"
#include <SFML/Audio.hpp>
#include"Button.h"

class Menu :public Screen
{
private:
	sf::Texture texture;
	sf::Texture backButton_texture;
	sf::RectangleShape backButton;
	sf::RectangleShape backArrow;
	sf::RectangleShape frontArrow;
	sf::Font font;
	sf::Music music;
	sf::SoundBuffer buffer;
	sf::Sound sound;
	sf::Text title;
	std::vector<sf::Text> currentText;
	std::vector<sf::Text> back_map_buffer;
	std::vector<sf::Text> front_map_buffer;
public:
	Menu(int, int);
	std::vector<std::string> readContentFile(std::string);
	void makeText(std::vector<std::string>&, int, int);
	void makeTitle(int, int);
	void draw_menu(sf::RenderWindow&);
	std::string run(sf::RenderWindow&);
	void goBack();
	void goFront();
};


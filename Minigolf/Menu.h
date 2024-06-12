#pragma once
#include "Screen.h"
#include <SFML/Audio.hpp>
#include"Button.h"
#include"BackArrow.h"

class Menu :public Screen
{
private:
	sf::Texture texture;
	sf::Texture backButton_texture;
	BackArrow backButton;
	BackArrow backArrow;
	BackArrow frontArrow;
	sf::SoundBuffer buffer;
	sf::Sound sound;
	sf::Text title;
	std::vector<sf::Text> currentText;
	std::vector<sf::Text> back_map_buffer;
	std::vector<sf::Text> front_map_buffer;
public:
	Menu(sf::RenderWindow&);
	std::vector<std::string> readContentFile(std::string);
	void makeText(std::vector<std::string>&, int, int);
	void makeTitle(int, int);
	std::vector<sf::Text> setupTexts(std::vector<std::string>&);
	void setTextsPositions(std::vector<sf::Text>&, int);
	void updateBuffers(std::vector<sf::Text>&, int);
	void draw_menu(sf::RenderWindow&);
	std::string run(sf::RenderWindow&);
	void goBack();
	void goFront();
};


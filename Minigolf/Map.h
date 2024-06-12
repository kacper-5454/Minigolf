#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include"Ball.h"
#include"Screen.h"
#include"BackgroundElement.h"

class Map : public Screen
{
private:
	std::vector<sf::Texture> textures;
	std::vector<std::unique_ptr<BackgroundElement>> elements;
	float gridSize=20.0;
	int width;
	int height;
	Ball ball;
	std::string name;
	sf::RectangleShape menuBackground;
	std::vector<sf::Text> texts;
	int strokeCounter =0;
	std::vector<sf::SoundBuffer> sound_buffers;
	std::vector<sf::Sound> sounds;
	sf::RectangleShape backButton;
public:
	Map(std::string, sf::RenderWindow&);
	void loadMapTextures(sf::RenderWindow&);
	void loadElements(std::string);
	void setTextures();
	void makeMenuBackground(int);
	void makeText(std::string, int);
	void draw(sf::RenderWindow&);
	std::string run(sf::RenderWindow&);
	bool collide();
	sf::SoundBuffer loadBuffer(std::string, sf::RenderWindow&);
	void loadBuffers(sf::RenderWindow&);
	void setSounds();
};


#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include"Ball.h"
#include"Screen.h"
#include"BackgroundElement.h"

class Map : public Screen
{
private:
	std::vector<sf::Texture> textures;
	std::vector<std::unique_ptr<BackgroundElement>> elements;
	float element_size;
	int width;
	int height;
	Ball ball;
	std::string name;
	sf::RectangleShape menuBackground;
	sf::Font font;
	std::vector<sf::Text> texts;
	int strokeCounter =-1;
public:
	Map(int, int, std::string, float);
	void loadMapTextures();
	void loadElements(std::string);
	void setTextures();
	void makeMenuBackground(int);
	void makeText(std::string, int);
	int getWidth();
	int getHeight();
	void draw(sf::RenderWindow&);
	char run(sf::RenderWindow&);
	bool collide();
};


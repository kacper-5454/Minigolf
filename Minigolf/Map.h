#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include"Ball.h"
#include"Screen.h"

class Map : public Screen
{
private:
	std::vector<sf::Texture> textures;
	std::vector<std::unique_ptr<sf::RectangleShape>> elements;
	float element_size = 20.0;
	int width;
	int height;
	Ball ball;
public:
	Map(std::string);
	void loadMapTextures();
	void loadElements(std::string);
	void setTextures();
	int getWidth();
	int getHeight();
	void draw(sf::RenderWindow&);
	char run(sf::RenderWindow&);
};


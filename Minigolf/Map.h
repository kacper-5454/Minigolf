#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include"Background_element.h"

class Map
{
private:
	std::vector<sf::Texture> textures;
	std::vector<Background_element> elements;
	float element_size;
	int width;
	int height;
	//std::string name;
public:
	Map(std::string, float);
	void loadMapTextures();
	void loadElements(std::string);
	void setTextures();
	int getWidth();
	int getHeight();
	void draw(sf::RenderWindow&);
};


#pragma once
#include "Screen.h"
#include"Screen.h"
#include"Button.h"
#include"Tile.h"
#include<set>

class Creator :  public Screen
{
private:
	float gridSize = 20.0;
	sf::Vector2i mousePosGrid;
	std::vector<Tile> icons;
	std::vector<sf::Texture> textures;
	bool isElementChosen;
	char currentElementToPlace;
	sf::RectangleShape menuBackground;
	sf::VertexArray grid;
	std::set<Tile, Tile::Comparator> tiles;
	sf::Font font;
	std::vector<sf::Text> menuText;
	sf::RectangleShape saveButton;
public:
	Creator(int, int);
	char run(sf::RenderWindow&);
	void draw(sf::RenderWindow&);
	void calculateMousePosGrid(sf::Vector2i, sf::RenderWindow&);
	void makeIcons();
	void loadTextures();
	void makeGrid(int, int);
	void placeOnScreen();
	void addTile(sf::Vector2f, int);
	void makeText();
};


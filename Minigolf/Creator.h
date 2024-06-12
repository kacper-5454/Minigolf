#pragma once
#include "Screen.h"
#include"Screen.h"
#include"Button.h"
#include"Tile.h"
#include"Textbox.h"
#include"BackArrow.h"
#include<set>

class Creator :  public Screen
{
private:
	float gridSize;
	sf::Vector2i mousePosGrid;
	std::vector<Tile> icons;
	std::vector<sf::Texture> textures;
	bool isElementChosen;
	char currentElementToPlace;
	sf::RectangleShape menuBackground;
	sf::VertexArray grid;
	std::set<Tile, Tile::Comparator> tiles;
	std::vector<sf::Text> menuText;
	sf::RectangleShape saveButton;
	BackArrow backButton;
	sf::Vector2f ball_pos;
	std::string currentErrorMessage = "No errors";
	Textbox textbox;
	sf::Sound sound;
	sf::SoundBuffer buffer;
public:
	Creator(sf::RenderWindow&);
	std::string run(sf::RenderWindow&);
	void draw(sf::RenderWindow&);
	void calculateMousePosGrid(sf::Vector2i, sf::RenderWindow&);
	void makeIcons();
	void loadTextures(sf::RenderWindow&);
	void placeOnScreen();
	void addTile(sf::Vector2f, int);
	void makeText();
	void prefillGrid(int, int);
	bool validateMap(int, int);
	void saveMap();
};


#pragma once
#include "Screen.h"
#include"Screen.h"
#include"Button.h"
#include"Tile.h"
#include"Textbox.h"
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
	sf::Font font;
	std::vector<sf::Text> menuText;
	sf::RectangleShape saveButton;
	sf::RectangleShape backButton;
	sf::Vector2f ball_pos;
	std::string currentErrorMessage = "No errors";
	Textbox textbox;
	sf::Sound sound;
	sf::SoundBuffer buffer;
	sf::Music music;
public:
	Creator(int, int);
	std::string run(sf::RenderWindow&);
	void draw(sf::RenderWindow&);
	void calculateMousePosGrid(sf::Vector2i, sf::RenderWindow&);
	void makeIcons();
	void loadTextures();
	void placeOnScreen();
	void addTile(sf::Vector2f, int);
	void makeText();
	void prefillGrid(int, int);
	bool validateMap(int, int);
	void saveMap();
};


#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include"Button.h"
#include"Screen.h"
class TitleScreen : public Screen
{
private:
	sf::Texture texture;
	Button play_button = Button("D:\\studia\\Programowanie Strukturalne i Obiektowe\\Minigolf\\Textures\\play.jpg",
		sf::Vector2f(220.0, 270.0));
	Button create_button = Button("D:\\studia\\Programowanie Strukturalne i Obiektowe\\Minigolf\\Textures\\create.png",
		sf::Vector2f(460.0, 270.0));
public:
	TitleScreen();
	char run(sf::RenderWindow&);
	void draw(sf::RenderWindow&);
	char detectButton(sf::Vector2i);
};


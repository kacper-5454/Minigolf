#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include<iostream>
class Ball : public sf::CircleShape
{
private:
	float velocity=0;
	sf::Texture texture;
public:
	Ball(std::string, sf::Vector2f);
};

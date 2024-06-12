#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Arrow : sf::Sprite
{
private:
	sf::Texture* texture;
public:
	Arrow() = default;
	void setArrowTexture(sf::Texture*);
	void update(sf::Vector2f, sf::Vector2f, float, float);
	void draw(sf::RenderWindow&);
};


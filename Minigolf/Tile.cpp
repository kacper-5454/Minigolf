#include "Tile.h"
#include<iostream>

bool Tile::isClicked(sf::Vector2i mouse_pos)
{
    sf::FloatRect bounds = this->getGlobalBounds();
    if (bounds.contains(static_cast<sf::Vector2f>(mouse_pos)))
    {
        return true;
    }
    else
    {
        return false;
    }
}

Tile::Tile(sf::Vector2f position, char tp)
{
	this->type = tp;
	this->setSize(sf::Vector2f(20.0, 20.0));
	this->setPosition(position);
}

void Tile::draw_icon(sf::RenderWindow& window)
{
	window.draw(static_cast<sf::RectangleShape&>(*this));
}

char Tile::getType()
{
    return this->type;
}


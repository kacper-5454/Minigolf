#include "Button.h"
#include<iostream>

Button::Button(std::string texture_file, sf::Vector2f position)
{
    if (texture.loadFromFile(texture_file))
    {
        this->setTexture(&texture);
    }
    else
    {
        std::cerr << "Error: Could not load texture from " << texture_file << std::endl;
    }
    this->setPosition(position);
    this->setSize(sf::Vector2f(120.0, 60.0));
}

Button::Button() {}

void Button::draw(sf::RenderWindow& window)
{
    window.draw(static_cast<sf::RectangleShape&>(*this));
}

bool Button::isClicked(sf::Vector2i mouse_pos)
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
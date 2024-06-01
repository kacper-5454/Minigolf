#include "Screen.h"
#include<iostream>

sf::Texture Screen::loadTexture(std::string path)
{
    sf::Texture texture;
    if (texture.loadFromFile(path))
    {
        return texture;
    }
    else
    {
        std::cerr << "Error: Could not load texture from " << path << std::endl;
    }
}

void Screen::handleResize(const sf::RenderWindow& window)
{
    sf::FloatRect visibleArea(0, 0, window.getSize().x, window.getSize().y);
    this->view.reset(visibleArea);
}

sf::View Screen::getView()
{
    return this->view;
}

void Screen::setView(sf::View v)
{
    this->view = v;
}

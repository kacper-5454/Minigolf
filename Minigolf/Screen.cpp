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
        throw("Couldnt load file from " + path);
    }
}
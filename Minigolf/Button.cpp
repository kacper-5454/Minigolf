#include "Button.h"
#include<iostream>

Button::Button(std::string text_string, sf::Vector2f position)
{
    if (this->texture.loadFromFile("D:\\studia\\Programowanie Strukturalne i Obiektowe\\Minigolf\\Textures\\button_background.png"))
    {
        this->setTexture(&this->texture);
    }
    else
    {
        std::cerr << "Error: Could not load button background texture" << std::endl;
    }
    this->setPosition(position);
    this->setSize(sf::Vector2f(120.0, 60.0));

    if (this->font.loadFromFile("D:\\studia\\Programowanie Strukturalne i Obiektowe\\Minigolf\\Fonts\\BarlowSemiCondensed-Bold.ttf"))
    {
        this->text.setFont(font);
    }
    else
    {
        std::cerr << "Couldnt load font while creating button" << std::endl;
    }
    this->text.setString(text_string);
    this->text.setCharacterSize(20.0);
    this->text.setFillColor(sf::Color(255, 49, 49));
    this->text.setOutlineThickness(2.0);
    this->text.setOutlineColor(sf::Color(130, 6, 0));
    float text_offset_x = this->getSize().x/2.0 - (this->text.getGlobalBounds().getSize().x)/2.0;
    float text_offset_y = this->getSize().y / 2.0 - (this->text.getGlobalBounds().getSize().y) / 2.0;
    this->text.setPosition(sf::Vector2f(position.x+text_offset_x, position.y+text_offset_y));
}

Button::Button() {}

void Button::draw(sf::RenderWindow& window)
{
    window.draw(static_cast<sf::RectangleShape&>(*this));
    window.draw(this->text);
}

bool Button::isClicked(sf::Vector2f mouse_pos)
{
    sf::FloatRect bounds = this->getGlobalBounds();
    if (bounds.contains(mouse_pos))
    {
        return true;
    }
    else
    {
        return false;
    }
}
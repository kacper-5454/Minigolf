#include "Button.h"
#include<iostream>

Button::Button(std::string text_string, sf::Vector2f position, sf::Vector2f size)
{
    if (this->texture.loadFromFile("..\\Textures\\button_background.png"))
    {
        this->setTexture(&this->texture);
    }
    else
    {
        std::cerr << "Error: Could not load button background texture" << std::endl;
    }
    this->setPosition(position);
    this->setSize(size);

    if (this->font.loadFromFile("..\\Fonts\\BarlowSemiCondensed-Bold.ttf"))
    {
        this->text.setFont(this->font);
    }
    else
    {
        std::cerr << "Couldnt load font while creating button" << std::endl;
    }
    this->text.setString(text_string);
    this->text.setCharacterSize(size.y/2.0);
    this->text.setFillColor(sf::Color(255, 49, 49));
    this->text.setOutlineThickness(2.0);
    this->text.setOutlineColor(sf::Color(130, 6, 0));
    float text_offset_x = this->getSize().x/2.0 - (this->text.getGlobalBounds().getSize().x)/2.0;
    float text_offset_y = this->getSize().y / 2.0 - (this->text.getGlobalBounds().getSize().y) / 2.0;
    this->text.setPosition(sf::Vector2f(position.x+text_offset_x, position.y+text_offset_y));

    if (this->buffer.loadFromFile("..\\Sounds\\button_click.wav"))
    {
        this->sound.setBuffer(this->buffer);
    }
    else
    {
        std::cerr << "Couldnt load button sound" << std::endl;
    }
}

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
        this->sound.play();
        return true;
    }
    else
    {
        return false;
    }
}
#include "Button.h"
#include<iostream>
#include"MessageBox.h"

Button::Button(std::string text_string, sf::Vector2f position, sf::Vector2f size, sf::RenderWindow& window)
{
    if (this->texture.loadFromFile("..\\Textures\\button_background.png"))
    {
        this->setTexture(&this->texture);
    }
    else
    {
        MessageBox messageBox("Couldn't load Button texture", "OK", window);
        messageBox.run(window);
        window.close();
    }
    this->setPosition(position);
    this->setSize(size);

    if (this->font.loadFromFile("..\\Fonts\\BarlowSemiCondensed-Bold.ttf"))
    {
        this->text.setFont(this->font);
    }
    else
    {
        MessageBox messageBox("Couldn't load font", "OK", window);
        messageBox.run(window);
        window.close();
    }
    this->text.setString(text_string);
    this->text.setCharacterSize(size.y/2.0);
    this->text.setFillColor(sf::Color(255, 49, 49));
    this->text.setOutlineThickness(2.0);
    this->text.setOutlineColor(sf::Color(130, 6, 0));
    float text_offset_x = this->getSize().x/2.0 - (this->text.getGlobalBounds().getSize().x)/2.0;
    float text_offset_y = this->getSize().y / 2.0 - (this->text.getGlobalBounds().getSize().y) / 2.0;
    this->text.setPosition(sf::Vector2f(position.x+text_offset_x, position.y+text_offset_y));
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
        return true;
    }
    else
    {
        return false;
    }
}
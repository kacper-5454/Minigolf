#include "Textbox.h"
#include<iostream>

Textbox::Textbox(sf::Vector2f size, sf::Vector2f position)
{
	this->setSize(size);
	this->setPosition(position);
    this->setOutlineColor(sf::Color(130, 6, 0));
    this->setOutlineThickness(-3.0);
    this->setFillColor(sf::Color::White);


    if (this->font.loadFromFile("..\\Fonts\\BarlowSemiCondensed-Bold.ttf"))
    {
        this->text.setFont(font);
    }
    else
    {
        std::cerr << "Couldnt load font while creating button" << std::endl;
    }

    this->text.setCharacterSize(15.0);
    this->text.setOutlineColor(sf::Color(130, 6, 0));
    this->text.setOutlineThickness(1.0);
    this->text.setFillColor(sf::Color(255, 49, 49));
    this->text.setPosition(position);
}

void Textbox::draw(sf::RenderWindow& window)
{
    window.draw(static_cast<sf::RectangleShape&>(*this));
    if (!this->text_string.empty())
    {
        window.draw(this->text);
    }
}

void Textbox::appendString(char ch)
{
    this->text_string += ch;
    this->text.setString(this->text_string);
}

void Textbox::backspace()
{
    this->text_string.erase(this->text_string.length() - 1, 1);
    this->text.setString(this->text_string);
}

std::string Textbox::getString()
{
    return this->text_string;
}

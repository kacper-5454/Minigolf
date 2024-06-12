#include "Textbox.h"
#include<iostream>
#include"MessageBox.h"

void Textbox::setupText(sf::Vector2f position, sf::RenderWindow& window)
{
    if (this->font.loadFromFile("..\\Fonts\\BarlowSemiCondensed-Bold.ttf"))
    {
        this->text.setFont(font);
    }
    else
    {
        MessageBox messageBox("Couldn't load font", "OK", window);
        messageBox.run(window);
        window.close();
    }
    this->text.setCharacterSize(15.0);
    this->text.setOutlineColor(sf::Color(130, 6, 0));
    this->text.setOutlineThickness(1.0);
    this->text.setFillColor(sf::Color(255, 49, 49));
    this->text.setPosition(position);
}

Textbox::Textbox(sf::Vector2f size, sf::Vector2f position, sf::RenderWindow& window)
{
	this->setSize(size);
	this->setPosition(position);
    this->setOutlineColor(sf::Color(130, 6, 0));
    this->setOutlineThickness(-3.0);
    this->setFillColor(sf::Color::White);
    this->setupText(position, window);
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
    if (this->text_string.length() > 0)
    {
        this->text_string.erase(this->text_string.length() - 1, 1);
        this->text.setString(this->text_string);
    }
}

std::string Textbox::getString()
{
    return this->text_string;
}

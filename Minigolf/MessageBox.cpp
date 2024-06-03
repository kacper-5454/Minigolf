#include "MessageBox.h"
#include<iostream>

MessageBox::MessageBox(std::string text, std::string button_text, int windowSizeX, int windowSizeY):
    sf::RectangleShape(sf::Vector2f(260.0, 140.0)),
    button(button_text, sf::Vector2f(windowSizeX / 2.0 - 30.0,
        windowSizeY / 2.0 + this->getSize().y / 2.0 - 32.0), sf::Vector2f(60.0, 30.0))
{
    if (this->texture.loadFromFile("..\\Textures\\message_box_background.png"))
    {
        this->setTexture(&this->texture);
    }
    else
    {
        std::cerr << "Error: Could not load messagebox background texture" << std::endl;
    }

    this->setPosition(sf::Vector2f(windowSizeX / 2.0 - this->getSize().x / 2.0, windowSizeY / 2.0 - this->getSize().y / 2.0));
    this->setOutlineColor(sf::Color(130, 6, 0));
    this->setOutlineThickness(5.0);
    
    if (this->font.loadFromFile("D:\\studia\\Programowanie Strukturalne i Obiektowe\\Minigolf\\Fonts\\BarlowSemiCondensed-Bold.ttf"))
    {
        this->text.setFont(font);
    }
    else
    {
        std::cerr << "Couldnt load font while creating messagebox" << std::endl;
    }
    this->text.setCharacterSize(20.0);
    this->text.setString(text);
    this->text.setFillColor(sf::Color(255, 49, 49));
    this->text.setOutlineThickness(2.0);
    this->text.setOutlineColor(sf::Color(130, 6, 0));
    float text_offset_x = this->getSize().x/2.0 - (this->text.getGlobalBounds().getSize().x)/2.0;
    float text_offset_y = this->getSize().y / 3.0 - (this->text.getGlobalBounds().getSize().y) / 3.0;
    this->text.setPosition(sf::Vector2f(this->getPosition().x + text_offset_x, this->getPosition().y + text_offset_y));
}

void MessageBox::draw_message(sf::RenderWindow& window)
{
    window.draw(static_cast<sf::RectangleShape&>(*this));
    window.draw(this->text);
    this->button.draw(window);
}

bool MessageBox::run(sf::RenderWindow& window)
{
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
                sf::Vector2f mouse_pos_view = window.mapPixelToCoords(mouse_pos, window.getView());
                if (this->button.isClicked(mouse_pos_view))
                {
                    return true;
                }
            }
        }
        this->draw_message(window);
        window.display();
    }
}
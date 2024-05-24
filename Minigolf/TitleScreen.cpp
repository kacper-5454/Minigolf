#include "TitleScreen.h"
#include<iostream>

TitleScreen::TitleScreen()
{
    this->setSize(sf::Vector2f(800, 450));
    this->setPosition(sf::Vector2f(0.0, 0.0));
    if (!texture.loadFromFile("D:\\studia\\Programowanie Strukturalne i Obiektowe\\Minigolf\\Textures\\minigolf.jpg"))
    {
        std::cerr << "Couldnt load ball texture" << std::endl;
    }
    else
    {
        this->setTexture(&texture);
    }
}

void TitleScreen::draw(sf::RenderWindow& window)
{
    window.draw(static_cast<sf::RectangleShape&>(*this));
    play_button.draw(window);
    create_button.draw(window);
}

char TitleScreen::detectButton(sf::Vector2i mouse_pos)
{
    if (play_button.isClicked(mouse_pos))
    {
        return 'p';
    }
    else if (create_button.isClicked(mouse_pos))
    {
        return 'c';
    }
    else
    {
        return 'n';
    }
}

char TitleScreen::run(sf::RenderWindow& window)
{
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
                    char whichButton= this->detectButton(mouse_pos);
                    switch (whichButton)
                    {
                    case 'p':
                        return 'p';
                        break;
                    case 'c':
                        return 'c';
                        break;
                    case 'n':
                        break;
                    default:
                        std::cerr << "Couldn't identify clicked button" << std::endl;
                        break;
                    }
                }
            }
        }
        window.clear(sf::Color::Black);
        this->draw(window);
        window.display();
    }
}

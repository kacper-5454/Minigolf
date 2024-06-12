#include "TitleScreen.h"
#include<iostream>
#include"MessageBox.h"

void TitleScreen::makeTitle(sf::RenderWindow& window)
{
    if (!this->font.loadFromFile("..\\Fonts\\BarlowSemiCondensed-Bold.ttf"))
    {
        MessageBox messageBox("Couldn't load font", "OK", window);
        messageBox.run(window);
        window.close();
    }
    this->title.setFont(this->font);
    this->title.setString("MINIGOLF");
    this->title.setCharacterSize(120);
    float text_pos_x = (static_cast<float>(window.getSize().x) - this->title.getGlobalBounds().getSize().x) / 2.0;
    this->title.setPosition(sf::Vector2f(text_pos_x, 100.0));
    this->title.setFillColor(sf::Color(255, 49, 49));
    this->title.setOutlineThickness(5.0);
    this->title.setOutlineColor(sf::Color(130, 6, 0));
}

TitleScreen::TitleScreen(sf::RenderWindow & window) :
    play_button("PLAY", sf::Vector2f(220.0, 270.0), sf::Vector2f(120.0, 60.0), window),
    create_button("CREATE", sf::Vector2f(460.0, 270.0), sf::Vector2f(120.0, 60.0), window)
{
    this->setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
    this->setPosition(sf::Vector2f(0.0, 0.0));
    try
    {
        this->texture = this->loadTexture("..\\Textures\\title_background.jpg");        
    }
    catch(...)
    {
        MessageBox messageBox("Couldn't load TitleScreen background", "OK", window);
        messageBox.run(window);
        window.close();
    }
    this->setTexture(&this->texture);
    this->makeTitle(window);

    if (this->buffer.loadFromFile("..\\Sounds\\button_click.wav"))
    {
        this->sound.setBuffer(this->buffer);
    }
    else
    {
        MessageBox messageBox("Couldn't load TitleScreen sound buffer", "OK", window);
        messageBox.run(window);
        window.close();
    }
}

void TitleScreen::draw(sf::RenderWindow& window)
{
    window.draw(static_cast<sf::RectangleShape&>(*this));
    window.draw(this->title);
    play_button.draw(window);
    create_button.draw(window);
}

char TitleScreen::detectButton(sf::Vector2f mouse_pos_view)
{
    if (play_button.isClicked(mouse_pos_view))
    {
        return 'p';
    }
    else if (create_button.isClicked(mouse_pos_view))
    {
        return 'c';
    }
    else
    {
        return 'n';
    }
}

std::string TitleScreen::run(sf::RenderWindow& window)
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

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
                    char whichButton= this->detectButton(static_cast<sf::Vector2f>(mouse_pos));
                    switch (whichButton)
                    {
                    case 'p':
                        return "play";
                        break;
                    case 'c':
                        return "create";
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
    return "";
}

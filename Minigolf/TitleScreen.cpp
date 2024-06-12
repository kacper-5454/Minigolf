#include "TitleScreen.h"
#include<iostream>

TitleScreen::TitleScreen(int windowSizeX, int windowSizeY)
{
    this->setSize(sf::Vector2f(windowSizeX, windowSizeY));
    this->setPosition(sf::Vector2f(0.0, 0.0));
    if (!this->texture.loadFromFile("..\\Textures\\title_background.jpg"))
    {
        std::cerr << "Couldnt load title background texture" << std::endl;
    }
    else
    {
        this->setTexture(&this->texture);
    }
    
    if (!this->font.loadFromFile("..\\Fonts\\BarlowSemiCondensed-Bold.ttf"))
    {
        std::cerr << "Couldnt load font" << std::endl;
    }
    else
    {
        this->title.setFont(this->font);
    }

    this->title.setString("MINIGOLF");
    this->title.setCharacterSize(120);
    float text_pos_x = (static_cast<float>(windowSizeX) - this->title.getGlobalBounds().getSize().x)/2.0;
    this->title.setPosition(sf::Vector2f(text_pos_x, 100.0));
    this->title.setFillColor(sf::Color(255, 49, 49));
    this->title.setOutlineThickness(5.0);
    this->title.setOutlineColor(sf::Color(130, 6, 0));
    if (!this->music.openFromFile("..\\Sounds\\intro_music.wav"))
    {
        std::cerr << "Couldnt load intro music" << std::endl;
    }
    music.setLoop(true);
    music.setVolume(25);
}

void TitleScreen::draw(sf::RenderWindow& window)
{
    window.setView(getView());
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
    this->music.play();
    this->setView(window.getDefaultView());
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
                
            if (event.type == sf::Event::Resized)
            {
                handleResize(window);
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
                    sf::Vector2f mouse_pos_view = window.mapPixelToCoords(mouse_pos, getView());
                    char whichButton= this->detectButton(mouse_pos_view);
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

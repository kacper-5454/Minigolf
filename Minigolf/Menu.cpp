#include "Menu.h"
#include<iostream>
#include<fstream>

std::vector<std::string> Menu::readContentFile(std::string source_path)
{
    std::vector<std::string> strings;
    std::fstream content_list(source_path);
    if (content_list.is_open())
    {
        std::string name;
        while (getline(content_list, name))
        {
            strings.emplace_back(name);
        }
    }
    return strings;
}

void Menu::makeTitle(int windowSizeX, int windowSizeY)
{
    this->title.setCharacterSize(30.0);
    this->title.setFillColor(sf::Color(255, 49, 49));
    this->title.setOutlineColor(sf::Color(130, 6, 0));
    this->title.setOutlineThickness(2.0);
    this->title.setFont(this->font);
    this->title.setString("Select level");
    this->title.setPosition(windowSizeX / 2.0 - this->title.getGlobalBounds().width / 2.0, 30.0);
}

void Menu::makeText(std::vector<std::string>& strings, int windowSizeX, int windowSizeY)
{
    std::vector<sf::Text> texts;
    for (const auto& str : strings)
    {
        sf::Text text;
        text.setCharacterSize(20);
        text.setFillColor(sf::Color(255, 49, 49));
        text.setOutlineColor(sf::Color(130, 6, 0));
        text.setOutlineThickness(2);
        text.setFont(this->font);
        text.setString(str);
        texts.emplace_back(text);
    }

    int elementsToDisplay = std::min(21, static_cast<int>(texts.size()));
    for (int i = 0; i < elementsToDisplay; i++)
    {
        if (i <= 6)
        {
            texts[i].setPosition(50, 100 + i * 40);
        }
        else if (i <= 13)
        {
            texts[i].setPosition(300, 100 + (i - 7) * 40);
        }
        else
        {
            texts[i].setPosition(550, 100 + (i - 14) * 40);
        }
    }

    this->currentText.assign(texts.begin(), texts.begin() + elementsToDisplay);
    if (texts.size() > elementsToDisplay)
    {
        this->front_map_buffer.assign(texts.begin() + elementsToDisplay, texts.end());
    }
    else
    {
        this->front_map_buffer.clear();
    }
    this->back_map_buffer.clear();
}

Menu::Menu(int windowSizeX, int windowSizeY)
{
    this->setSize(sf::Vector2f(windowSizeX, windowSizeY));
    this->setPosition(sf::Vector2f(0.0, 0.0));
	this->texture = this->loadTexture("..\\Textures\\menu_background.jpg");
	this->setTexture(&this->texture);

	this->backButton_texture = this->loadTexture("..\\Textures\\back_arrow.png");
	this->backButton.setTexture(&this->backButton_texture);
	this->backButton.setSize(sf::Vector2f(20.0, 20.0));
	this->backButton.setPosition(sf::Vector2f(20.0, 20.0));

    this->backArrow.setTexture(&this->backButton_texture);
    this->backArrow.setSize(sf::Vector2f(20.0, 20.0));
    this->backArrow.setPosition(sf::Vector2f(50.0, windowSizeY-50.0));

    this->frontArrow.setTexture(&this->backButton_texture);
    this->frontArrow.setSize(sf::Vector2f(20.0, 20.0));
    this->frontArrow.setRotation(180);
    this->frontArrow.setPosition(sf::Vector2f(windowSizeX - 50.0, windowSizeY - 30.0));

	std::vector<std::string> name_strings = readContentFile("..\\Maps\\map names.txt");
    if (!this->font.loadFromFile("..\\Fonts\\BarlowSemiCondensed-Bold.ttf"))
    {
        std::cerr << "Couldnt load font" << std::endl;
    }
    makeTitle(windowSizeX, windowSizeY);
    makeText(name_strings, windowSizeX, windowSizeX);

    if (this->buffer.loadFromFile("..\\Sounds\\button_click.wav"))
    {
        this->sound.setBuffer(this->buffer);
    }
    else
    {
        std::cerr << "Couldnt load button sound" << std::endl;
    }

    if (!this->music.openFromFile("..\\Sounds\\intro_music.wav"))
    {
        std::cerr << "Couldnt load intro music" << std::endl;
    }
    music.setLoop(true);
    music.setVolume(6);
}

void Menu::draw_menu(sf::RenderWindow& window)
{
    window.draw(static_cast<sf::RectangleShape&>(*this));
    window.draw(this->backButton);
    window.draw(this->backArrow);
    window.draw(this->frontArrow);
    window.draw(this->title);
    for (auto& el : this->currentText)
    {
        window.draw(el);
    }
}

void Menu::goBack()
{
    if (!this->back_map_buffer.empty())
    {
        int elementsToMove = std::min(21, static_cast<int>(this->back_map_buffer.size()));
        int start = this->back_map_buffer.size() - elementsToMove;
        int end = this->back_map_buffer.size();

        for (int i = start; i < end; i++)
        {
            if (i-start <= 6)
            {
                this->back_map_buffer[i].setPosition(50.0, 100.0 + (i - start) * 40.0);
            }
            else if (i-start <= 13)
            {
                this->back_map_buffer[i].setPosition(300.0, 100.0 + (i - start - 7) * 40.0);
            }
            else
            {
                this->back_map_buffer[i].setPosition(550.0, 100.0 + (i - start - 14) * 40.0);
            }
        }

        this->front_map_buffer.insert(this->front_map_buffer.end(), this->currentText.begin(), this->currentText.end());
        this->currentText.assign(this->back_map_buffer.begin() + start, this->back_map_buffer.begin() + end);
        this->back_map_buffer.erase(this->back_map_buffer.begin() + start, this->back_map_buffer.begin() + end);
    }
}

void Menu::goFront()
{
    if (!this->front_map_buffer.empty())
    {
        int elementsToMove = std::min(21, static_cast<int>(this->front_map_buffer.size()));

        for (int i = 0; i < elementsToMove ; i++)
        {
            if (i <= 6)
            {
                this->front_map_buffer[i].setPosition(50.0, 100.0 + i * 40.0);
            }
            else if (i <= 13)
            {
                this->front_map_buffer[i].setPosition(300.0, 100.0 + (i - 7) * 40.0);
            }
            else
            {
                this->front_map_buffer[i].setPosition(550.0, 100.0 + (i - 14) * 40.0);
            }
        }

        this->back_map_buffer.insert(this->back_map_buffer.end(), this->currentText.begin(), this->currentText.end());
        this->currentText.assign(this->front_map_buffer.begin(), this->front_map_buffer.begin() + elementsToMove);
        this->front_map_buffer.erase(this->front_map_buffer.begin(), this->front_map_buffer.begin() + elementsToMove);
    }
}

std::string Menu::run(sf::RenderWindow& window)
{
    this->setView(window.getDefaultView());
    this->music.play();
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

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
                if (this->backButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse_pos)))
                {
                    this->sound.play();
                    return "back";
                }
                if (this->backArrow.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse_pos)))
                {
                    this->sound.play();
                    goBack();
                }
                if (this->frontArrow.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse_pos)))
                {
                    this->sound.play();
                    goFront();
                }
                for (auto &el : this->currentText)
                {
                    if (el.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse_pos)))
                    {
                        return static_cast<std::string>(el.getString());
                    }
                }
            }
        }

        window.clear(sf::Color::Black);
        this->draw_menu(window);
        window.display();
    }
    return "";
}

#include "Menu.h"
#include<iostream>
#include<fstream>
#include"MessageBox.h"

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

std::vector<sf::Text> Menu::setupTexts(std::vector<std::string>& strings)
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
    return texts;
}

void Menu::setTextsPositions(std::vector<sf::Text>& texts, int elementsToDisplay)
{
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
}

void Menu::updateBuffers(std::vector<sf::Text>& texts, int elementsToDisplay)
{
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

void Menu::makeText(std::vector<std::string>& strings, int windowSizeX, int windowSizeY)
{
    std::vector<sf::Text> texts = this->setupTexts(strings);
    int elementsToDisplay = std::min(21, static_cast<int>(texts.size()));
    this->setTextsPositions(texts, elementsToDisplay);
    this->updateBuffers(texts, elementsToDisplay);
}

Menu::Menu(sf::RenderWindow& window) :
    backButton(sf::Vector2f(20.0, 20.0), window),
    backArrow(sf::Vector2f(50.0, window.getSize().y - 50.0), window),
    frontArrow(sf::Vector2f(window.getSize().x - 50.0, window.getSize().y - 30.0), window)
{
    this->setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
    this->setPosition(sf::Vector2f(0.0, 0.0));
    try
    {
        this->texture = this->loadTexture("..\\Textures\\menu_background.jpg");
    }
    catch (...)
    {
        MessageBox messageBox("Couldn't load Menu background", "OK", window);
        messageBox.run(window);
        window.close();
    }

	this->setTexture(&this->texture);

    this->frontArrow.setRotation(180);

	std::vector<std::string> name_strings = readContentFile("..\\Maps\\map names.txt");
    if (!this->font.loadFromFile("..\\Fonts\\BarlowSemiCondensed-Bold.ttf"))
    {
        MessageBox messageBox("Couldn't load font", "OK", window);
        messageBox.run(window);
        window.close();
    }
    makeTitle(window.getSize().x, window.getSize().y);
    makeText(name_strings, window.getSize().x, window.getSize().y);

    if (this->buffer.loadFromFile("..\\Sounds\\button_click.wav"))
    {
        this->sound.setBuffer(this->buffer);
    }
    else
    {
        MessageBox messageBox("Couldn't load Menu sound buffer", "OK", window);
        messageBox.run(window);
        window.close();
    }
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
                        this->sound.play();
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

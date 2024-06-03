#include "Map.h"
#include<iostream>
#include"Grass.h"
#include"Sand.h"
#include"Water.h"
#include"Wall.h"
#include"Hole.h"
#include"MessageBox.h"
#include<string>
#include<fstream>
#include<sstream>

std::vector<std::string> readFile(std::string source_path)
{
    std::vector<std::string> strings;
    std::fstream map_file(source_path);
    if (map_file.is_open())
    {
        std::stringstream map_stream;
        map_stream << map_file.rdbuf();

        std::string map_string = map_stream.str();

        std::string ball_pos_x_string = map_string.substr(0, 3);
        strings.emplace_back(ball_pos_x_string);

        std::string ball_pos_y_string = map_string.substr(3, 3);
        strings.emplace_back(ball_pos_y_string);

        std::string background_string = map_string.substr(6, map_string.length() - 6);
        strings.emplace_back(background_string);
    }
    if (strings.size() == 3)
    {
        return strings;
    }
    else
    {
        std::cerr << "Data vector contains wrong number of elements" << std::endl;
    }
}

void Map::loadElements(std::string background_data)
{
    float x_pos = 0.0;
    float y_pos = 0.0;
    for (int i = 0; i < background_data.length(); i++)
    {
        switch (background_data[i])
        {
        case 'g':
            this->elements.emplace_back(std::make_unique<Grass>(Grass(sf::Vector2f(x_pos, y_pos), element_size)));
            break;
        case 's':
            this->elements.emplace_back(std::make_unique <Sand>(Sand(sf::Vector2f(x_pos, y_pos), element_size)));
            break;
        case 'a':
            this->elements.emplace_back(std::make_unique <Water>(Water(sf::Vector2f(x_pos, y_pos), element_size)));
            break;
        case 'w':
            this->elements.emplace_back(std::make_unique<Wall>(Wall(sf::Vector2f(x_pos, y_pos), element_size)));
            break;
        case 'h':
            this->elements.emplace_back(std::make_unique<Hole>(Hole(sf::Vector2f(x_pos, y_pos), element_size)));
            break;
        case 'n':
            this->width = x_pos + element_size;
            x_pos = -element_size;
            y_pos += element_size;
            break;
        default:
            std::cerr << "Error in map data" << std::endl;
            break;
        }
        x_pos += element_size;
        this->height = y_pos + element_size;
    }

}

void Map::loadMapTextures()
{
    //Grass [0]
    textures.emplace_back(loadTexture("..\\Textures\\grass_light.jpg"));
    //Sand [2]
    textures.emplace_back(loadTexture("..\\Textures\\sand.jpg"));
    //Water [3]
    textures.emplace_back(loadTexture("..\\Textures\\water.jpg"));
    //Wall [4]
    textures.emplace_back(loadTexture("..\\Textures\\wall.jpg"));
    //Hole [5]
    textures.emplace_back(loadTexture("..\\Textures\\hole.png"));
}

void Map::setTextures()
{
    for (const auto &el : elements)
    {
        if (auto grass = dynamic_cast<Grass*>(el.get()))
        {
            grass->setTexture(&textures[0]);
        }
        else if (auto wall = dynamic_cast<Wall*>(el.get()))
        {
            wall->setTexture(&textures[3]);
        }
        else if (auto sand = dynamic_cast<Sand*>(el.get()))
        {
            sand->setTexture(&textures[1]);
        }
        else if (auto water = dynamic_cast<Water*>(el.get()))
        {
            water->setTexture(&textures[2]);
        }
        else if (auto hole = dynamic_cast<Hole*>(el.get()))
        {
            hole->setTexture(&textures[4]);
        }
        else
        {
            std::cerr << "Coulnd match element to type" << std::endl;
        }
    }
}

void Map::makeMenuBackground(int windowSizeX)
{
    this->menuBackground.setPosition(0.0, 0.0);
    this->menuBackground.setSize(sf::Vector2f(windowSizeX, this->element_size));
    this->menuBackground.setFillColor(sf::Color(255, 49, 49));
    this->menuBackground.setOutlineColor(sf::Color(130, 6, 0));
    this->menuBackground.setOutlineThickness(2.0);
}

void Map::makeText(std::string name, int windowSizeX)
{
    std::vector<std::string> strings = { name, "Number of strokes: ", std::to_string(this->strokeCounter) };
    for (int i = 0; i < strings.size(); i++)
    {
        sf::Text text;
        text.setCharacterSize(20.0);
        text.setFillColor(sf::Color(255, 49, 49));
        text.setOutlineColor(sf::Color(130, 6, 0));
        text.setOutlineThickness(2.0);
        text.setFont(this->font);
        text.setString(strings[i]);
        this->texts.emplace_back(text);
    }
    this->texts[0].setPosition(sf::Vector2f(0.0, 0.0));
    this->texts[1].setPosition(sf::Vector2f(windowSizeX/2.0, 0.0));
    this->texts[2].setPosition(sf::Vector2f(this->texts[1].getGlobalBounds().getPosition().x +
        this->texts[1].getGlobalBounds().getSize().x, 0.0));
}

Map::Map(int windowSizeX, int windowSizeY, std::string name, float gridSize)
{
    this->element_size = gridSize;
    this->name = name;
    std::string source_path = "..\\Maps\\" + this->name + ".txt";
    this->loadMapTextures();

    std::vector<std::string> data = readFile(source_path);
    this->loadElements(data[2]);

    float ball_pos_x = std::stof(data[0]);
    float ball_pos_y = std::stof(data[1]);
    this->ball = Ball(sf::Vector2f(ball_pos_x, ball_pos_y));
    
    this->setTextures();

    this->makeMenuBackground(windowSizeX);

    if (!this->font.loadFromFile("..\\Fonts\\BarlowSemiCondensed-Bold.ttf"))
    {
        std::cerr << "Couldnt load font" << std::endl;
    }
    else
    {
        this->makeText(name, windowSizeX);
    }
}

int Map::getWidth()
{
    return this->width;
}

int Map::getHeight()
{
    return this->height;
}

void Map::draw(sf::RenderWindow& window)
{
    window.setView(getView());
    window.draw(this->menuBackground);
    for (auto el : this->texts)
    {
        window.draw(el);
    }
    for (const auto& el : this->elements)
    {
        window.draw(*el);
    }
    this->ball.draw_ball(window);
}

bool Map::collide()
{
    for (auto &el : elements)
    {
        if (el->collide(this->ball))
        {
            return true;
        }
    }
    return false;
}

char Map::run(sf::RenderWindow& window)
{
    sf::Clock clock;
    sf::Time elapsed;

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
               
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                this->ball.update_status(window);
            }

            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
            {
                this->ball.release(window);
                this->strokeCounter++;
                this->texts[2].setString(std::to_string(this->strokeCounter));
            }
        }

        /*if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            this->ball.update_status(window);
        }*/

        bool isHoleScored = collide();
        if (isHoleScored)
        {
            std::string messageBoxString = "Map " + this->name + " \ncompleated in \n" + std::to_string(this->strokeCounter) +
                " strokes!";
            MessageBox messagebox = MessageBox(messageBoxString, "OK", window.getSize().x, window.getSize().y);
            messagebox.run(window);
            return 'w';
        }

        //moving
        elapsed = clock.restart();
        float deltaSeconds = elapsed.asSeconds();
        this->ball.move_ball(deltaSeconds);
        
        //drawing and displaying
        window.clear(sf::Color::Black);
        this->draw(window);
        window.display();
    }
    return 'w';
}


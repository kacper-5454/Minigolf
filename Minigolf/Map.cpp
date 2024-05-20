#include "Map.h"
#include<fstream>
#include<sstream>
#include<iostream>
#include"Background_type.h"
#include"Background_element.h"

void Map::loadMapTextures()
{
    sf::Texture texture;

    //Grass
    if (texture.loadFromFile("D:\\studia\\Programowanie Strukturalne i Obiektowe\\Minigolf\\Textures\\grass_medium.jpg"))
    {
        this->textures.emplace_back(texture);
    }
    else
    {
        std::cerr << "Error: Could not load texture" << std::endl;
    }

    //Sand
    if (texture.loadFromFile("D:\\studia\\Programowanie Strukturalne i Obiektowe\\Minigolf\\Textures\\sand.jpg"))
    {
        this->textures.emplace_back(texture);
    }
    else
    {
        std::cerr << "Error: Could not load texture" << std::endl;
    }

    //Water
    if (texture.loadFromFile("D:\\studia\\Programowanie Strukturalne i Obiektowe\\Minigolf\\Textures\\water.jpg"))
    {
        this->textures.emplace_back(texture);
    }
    else
    {
        std::cerr << "Error: Could not load texture" << std::endl;
    }

    //Wall
    if (texture.loadFromFile("D:\\studia\\Programowanie Strukturalne i Obiektowe\\Minigolf\\Textures\\wall.jpg"))
    {
        this->textures.emplace_back(texture);
    }
    else
    {
        std::cerr << "Error: Could not load texture" << std::endl;
    }

    //Hole
    if (texture.loadFromFile("D:\\studia\\Programowanie Strukturalne i Obiektowe\\Minigolf\\Textures\\grass_dark.jpg"))
    {
        this->textures.emplace_back(texture);
    }
    else
    {
        std::cerr << "Error: Could not load texture" << std::endl;
    }
}

void Map::loadElements(std::string source_path)
{
    std::fstream map_file(source_path);
    if (map_file.is_open())
    {
        std::stringstream map_stream;
        map_stream << map_file.rdbuf();
        std::string map_string = map_stream.str();
        float x_pos = 0;
        float y_pos = 0;
        for (int i = 0; i < map_string.length(); i++)
        {
            switch (map_string[i])
            {
            case 'g':
                this->elements.emplace_back(Background_element(Grass, sf::Vector2f(x_pos, y_pos), element_size));
                break;
            case 's':
                this->elements.emplace_back(Background_element(Sand, sf::Vector2f(x_pos, y_pos), element_size));
                break;
            case 'a':
                this->elements.emplace_back(Background_element(Water, sf::Vector2f(x_pos, y_pos), element_size));
                break;
            case 'w':
                this->elements.emplace_back(Background_element(Wall, sf::Vector2f(x_pos, y_pos), element_size));
                break;
            case 'h':
                this->elements.emplace_back(Background_element(Hole, sf::Vector2f(x_pos, y_pos), element_size));
                break;
            case 'n':
                this->width = x_pos+element_size;
                x_pos = -element_size;
                y_pos +=element_size;
                break;
            default:
                std::cerr << "Error in map data" << std::endl;
                break;
            }
            x_pos += element_size;
            this->height = y_pos+element_size;
        }
    }
}

void Map::setTextures()
{
    for (auto &el : elements)
    {
        switch (el.getType())
        {
        case Grass:
            el.setTexture(&textures[0]);
            break;
        case Sand:
            el.setTexture(&textures[1]);
            break;
        case Water:
            el.setTexture(&textures[2]);
            break;
        case Wall:
            el.setTexture(&textures[3]);
            break;
        case Hole:
            el.setTexture(&textures[4]);
            break;
        default:
            std::cerr << "Coundn't match texture to element" << std::endl;
            break;
        }
    }
}

Map::Map(std::string source_path, float size)
{
    this->element_size = size;
    this->loadMapTextures();
    this->loadElements(source_path);
    this->setTextures();
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
    for (auto& el : elements)
    {
        window.draw(el);
    }
}


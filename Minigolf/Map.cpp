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
    //Sand [1]
    textures.emplace_back(loadTexture("..\\Textures\\sand.jpg"));
    //Water [2]
    textures.emplace_back(loadTexture("..\\Textures\\water.jpg"));
    //Wall [3]
    textures.emplace_back(loadTexture("..\\Textures\\wall.jpg"));
    //Hole [4]
    textures.emplace_back(loadTexture("..\\Textures\\hole.png"));
    //Arrow [5]
    textures.emplace_back(loadTexture("..\\Textures\\arrow.png"));
    //Back Button Icon [6]
    textures.emplace_back(loadTexture("..\\Textures\\back_arrow.png"));
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
    this->texts[0].setPosition(sf::Vector2f(40.0, 0.0));
    this->texts[1].setPosition(sf::Vector2f(windowSizeX/2.0, 0.0));
    this->texts[2].setPosition(sf::Vector2f(this->texts[1].getGlobalBounds().getPosition().x +
        this->texts[1].getGlobalBounds().getSize().x, 0.0));
}

sf::SoundBuffer Map::loadBuffer(std::string path)
{
    sf::SoundBuffer buffer;
    if (buffer.loadFromFile(path))
    {
        return buffer;
    }
    else
    {
        std::cerr << "Couldnt load sound from "<< path << std::endl;
    }
}

void Map::loadBuffers()
{
    //Sand [0]
    this->sound_buffers.emplace_back(loadBuffer("..\\Sounds\\ball_in_sand.wav")); 
    //Water [1]
    this->sound_buffers.emplace_back(loadBuffer("..\\Sounds\\water_splash.wav"));
    //Wall [2]
    this->sound_buffers.emplace_back(loadBuffer("..\\Sounds\\wall_hit.wav"));
    //Hole [3]
    this->sound_buffers.emplace_back(loadBuffer("..\\Sounds\\in_hole.wav"));
    //Button [4]
    this->sound_buffers.emplace_back(loadBuffer("..\\Sounds\\button_click.wav"));
}

void Map::setSounds()
{
    for (auto &el : this->sound_buffers)
    {
        sf::Sound sound;
        sound.setBuffer(el);
        this->sounds.emplace_back(sound);
    }
}

Map::Map(int windowSizeX, int windowSizeY, std::string name, float gridSize)
{
    this->element_size = gridSize;
    this->name = name;
    std::string source_path = "..\\Maps\\" + this->name + ".txt";
    this->loadMapTextures();

    std::vector<std::string> data = readFile(source_path);
    this->loadElements(data[2]);
    this->setTextures();

    float ball_pos_x = std::stof(data[0]);
    float ball_pos_y = std::stof(data[1]);
    this->ball = Ball(sf::Vector2f(ball_pos_x, ball_pos_y), &this->textures[5]);
    
    this->makeMenuBackground(windowSizeX);

    if (!this->font.loadFromFile("..\\Fonts\\BarlowSemiCondensed-Bold.ttf"))
    {
        std::cerr << "Couldnt load font" << std::endl;
    }
    else
    {
        this->makeText(name, windowSizeX);
    }

    this->backButton.setTexture(&this->textures[6]);
    this->backButton.setSize(sf::Vector2f(gridSize, gridSize));
    this->backButton.setPosition(sf::Vector2f(0.0, 0.0));

    loadBuffers();
    setSounds();

    if (!this->music.openFromFile("..\\Sounds\\intro_music.wav"))
    {
        std::cerr << "Couldnt load intro music" << std::endl;
    }
    music.setLoop(true);
    music.setVolume(6);
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
    window.draw(this->backButton);
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
        bool toPlay = true;
        bool ballMoving = ball.getMoving();
        int index = el->collide(this->ball);
        if (index >= 0 && index < this->sounds.size())
        {
            for (auto& elm : sounds)
            {
                if (elm.getStatus() == sf::SoundSource::Status::Playing)
                {
                    toPlay = false;
                }
            }

            if (ballMoving && toPlay)
            {
                this->sounds[index].play();
            }
        }

        if (index == 3)
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
    bool isLoadingTime = true;
    float loadingTime = 1.0;

    this->setView(window.getDefaultView());
    this->music.play();

    while (window.isOpen())
    {
        elapsed = clock.restart();
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

            if (!isLoadingTime && event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
            {
                if (!ball.getMoving())
                {
                    this->strokeCounter++;
                }
                this->ball.release(window);
                this->texts[2].setString(std::to_string(this->strokeCounter));
            }
        }

        if (!isLoadingTime && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            this->ball.update_status(window);
            if (this->backButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))))
            {
                this->sounds[4].play();
                return 'm';
            }
        }

        if (isLoadingTime && elapsed.asSeconds() - loadingTime < 0.0)
        {
            isLoadingTime = false;
        }

        bool isHoleScored = collide();
        if (isHoleScored)
        {
            std::string messageBoxString = "Map " + this->name + " \ncompleated in \n" + std::to_string(this->strokeCounter) +
                " strokes!";
            MessageBox messagebox = MessageBox(messageBoxString, "OK", window.getSize().x, window.getSize().y);
            messagebox.run(window);
            return 'm';
        }

        //moving
        float deltaSeconds = elapsed.asSeconds();
        this->ball.move_ball(deltaSeconds);
        
        //drawing and displaying
        window.clear(sf::Color::Black);
        this->draw(window);
        window.display();
    }
    return 'm';
}


#include "Creator.h"
#include<iostream>
#include<fstream>
#include<cmath>
#include<string>
#include"MessageBox.h"

void Creator::makeIcons()
{
    std::vector<char> types = { 'g', 's', 'w', 'a', 'h', 'b' };
    for (int i = 0; i < types.size(); i++)
    {
        this->icons.emplace_back(Tile(sf::Vector2f(120.0 + i * 90.0, 0.0), types[i], this->gridSize));
        this->icons[i].setTexture(&this->textures[i]);
    }
}

void Creator::loadTextures()
{
    this->textures.emplace_back(loadTexture("..\\Textures\\grass_light.jpg"));
    this->textures.emplace_back(loadTexture("..\\Textures\\sand.jpg"));
    this->textures.emplace_back(loadTexture("..\\Textures\\wall.jpg"));
    this->textures.emplace_back(loadTexture("..\\Textures\\water.jpg"));
    this->textures.emplace_back(loadTexture("..\\Textures\\hole.png"));
    this->textures.emplace_back(loadTexture("..\\Textures\\ball_on_grass_light.png"));
    this->textures.emplace_back(loadTexture("..\\Textures\\save_icon.png"));
    this->textures.emplace_back(loadTexture("..\\Textures\\back_arrow.png"));
}

void Creator::makeText()
{
    std::vector<std::string> strings = { "Grass", "Sand", "Wall", "Water", "Hole", "Ball", "Name"};
    for (int i = 0; i < strings.size(); i++)
    {
        sf::Text text;
        text.setString(strings[i]);
        text.setFont(this->font);
        text.setCharacterSize(20.0);
        text.setFillColor(sf::Color(255, 49, 49));
        text.setOutlineThickness(2.0);
        text.setOutlineColor(sf::Color(130, 6, 0));
        float text_offset_x = 40.0 - (text.getGlobalBounds().getSize().x) / 2.0;
        float text_offset_y = 10.0 - (text.getGlobalBounds().getSize().y) / 2.0;
        text.setPosition(sf::Vector2f(45.0+i*90.0 + text_offset_x, text_offset_y));
        menuText.emplace_back(text);
    }
}

void Creator::prefillGrid(int windowSizeX, int windowSizeY)
{
    int tile_amount_x = ceil(windowSizeX / this->gridSize);
    int tile_amount_y = ceil(windowSizeY / this->gridSize);

    for (int i = 0; i < tile_amount_x; i++)
    {
        Tile tile1 = Tile(sf::Vector2f(i*this->gridSize, this->gridSize), 'w', this->gridSize);
        tile1.setTexture(&this->textures[2]);
        tiles.insert(tile1);

        Tile tile2 = Tile(sf::Vector2f(i * this->gridSize, (tile_amount_y-1)*this->gridSize), 'w', this->gridSize);
        tile2.setTexture(&this->textures[2]);
        tiles.insert(tile2);
    }
    
    for (int i = 1; i < tile_amount_y-1; i++)
    {
        Tile tile1 = Tile(sf::Vector2f(0.0, (i + 1) * this->gridSize), 'w', this->gridSize);
        tile1.setTexture(&this->textures[2]);
        tiles.insert(tile1);

        for (int j = 1; j < tile_amount_x-1; j++)
        {
            Tile tile = Tile(sf::Vector2f(j*this->gridSize, (i + 1) * this->gridSize), 'g', this->gridSize);
            tile.setTexture(&this->textures[0]);
            tiles.insert(tile);
        }

        Tile tile2 = Tile(sf::Vector2f((tile_amount_x-1)*this->gridSize, (i + 1) * this->gridSize), 'w', this->gridSize);
        tile2.setTexture(&this->textures[2]);
        tiles.insert(tile2);
    }
}

Creator::Creator(int windowSizeX, int windowSizeY, float gS):
    textbox(sf::Vector2f(4 * gS, gS), sf::Vector2f(windowSizeX-7*gS, 0.0))
{
    this->gridSize = gS;
    this->isElementChosen = false;
    this->loadTextures();
    if (!this->font.loadFromFile("..\\Fonts\\BarlowSemiCondensed-Bold.ttf"))
    {
        std::cerr << "Couldnt load font" << std::endl;
    }
    this->makeText();
    this->makeIcons();

    this->menuBackground.setSize(sf::Vector2f(windowSizeX, this->gridSize));
    this->menuBackground.setPosition(sf::Vector2f(0.0, 0.0));
    this->menuBackground.setFillColor(sf::Color(255, 49, 49));
    this->menuBackground.setOutlineColor(sf::Color(130, 6, 0));
    this->menuBackground.setOutlineThickness(2.0);

    this->saveButton.setTexture(&this->textures[6]);
    this->saveButton.setSize(sf::Vector2f(this->gridSize, this->gridSize));
    this->saveButton.setPosition(sf::Vector2f(windowSizeX - 2*this->gridSize, 0.0));

    this->backButton.setTexture(&this->textures[7]);
    this->backButton.setSize(sf::Vector2f(this->gridSize, this->gridSize));
    this->backButton.setPosition(sf::Vector2f(0.0, 0.0));

    this->prefillGrid(windowSizeX, windowSizeY);

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

void Creator::draw(sf::RenderWindow& window)
{
    window.setView(getView());
    window.draw(grid);

    window.draw(this->menuBackground);
    window.draw(this->saveButton);
    window.draw(this->backButton);
    this->textbox.draw(window);

    for (auto &el : this->icons)
    {
        el.draw_icon(window);
    }
    for (auto& el : this->menuText)
    {
        window.draw(el);
    }

    for (auto el : this->tiles)
    {
        el.draw_icon(window);
    }
}

void Creator::calculateMousePosGrid(sf::Vector2i mouse_pos, sf::RenderWindow& window)
{
    if (mouse_pos.x >= 0 && mouse_pos.x <= window.getSize().x)
    {
        this->mousePosGrid.x = mouse_pos.x / static_cast<int> (this->gridSize);
    }
    else
    {
        this->mousePosGrid.x = -1;
    }

    if (mouse_pos.y >= 0 && mouse_pos.y <=window.getSize().y)
    {
        this->mousePosGrid.y = mouse_pos.y / static_cast<int> (this->gridSize);
    }
    else
    {
        this->mousePosGrid.y = -1;
    }
}

void Creator::addTile(sf::Vector2f tile_pos, int texture_index)
{
    Tile tile = Tile(tile_pos, this->currentElementToPlace, this->gridSize);
    tile.setTexture(&this->textures[texture_index]);

    auto it = this->tiles.find(tile);
    if (it != this->tiles.end())
    {
        this->tiles.erase(it);
    }
    this->tiles.insert(tile);
}

void Creator::placeOnScreen()
{
    if (this->mousePosGrid.x >= 0 && this->mousePosGrid.y > 0)
    {
        sf::Vector2f tile_pos(this->mousePosGrid.x * this->gridSize, this->mousePosGrid.y * this->gridSize);
        switch (this->currentElementToPlace)
        {
        case 'g':
            addTile(tile_pos, 0);
            break;
        case 's':
            addTile(tile_pos, 1);
            break;
        case 'w':
            addTile(tile_pos, 2);
            break;
        case 'a':
            addTile(tile_pos, 3);
            break;
        case 'h':
            addTile(tile_pos, 4);
            break;
        case 'b':
            addTile(tile_pos, 5);
            break;
        default:
            std::cerr << "Couldnt identify element to place" << std::endl;
        }
    }
}

bool Creator::validateMap(int windowSizeX, int windowSizeY)
{
    int ball_count = 0;
    int hole_count = 0;

    int tile_amount_x = ceil(windowSizeX / this->gridSize);
    int tile_amount_y = ceil(windowSizeY / this->gridSize);

    for (auto el : tiles)
    {
        if (el.getType() == 'b')
        {
            this->ball_pos = sf::Vector2f(el.getPosition().x + this->gridSize / 2.0, el.getPosition().y + this->gridSize/ 2.0);
            ball_count++;
        }
        else if (el.getType() == 'h')
        {
            hole_count++;
        }
        
        bool topPerimeter = (el.getPosition().y == this->gridSize);
        bool bottomPerimeter = (el.getPosition().y == (tile_amount_y - 1) * this->gridSize);
        bool leftPerimeter = (el.getPosition().x == 0.0);
        bool rightPerimeter = (el.getPosition().x == (tile_amount_x - 1) * this->gridSize);
        
        bool isPerimeter = topPerimeter || bottomPerimeter || leftPerimeter || rightPerimeter;
 
        if (isPerimeter)
        {
            if (el.getType() != 'w')
            {
                this->currentErrorMessage = "Perimeter isn't made entirely\nout of wall tile ";
                return false;
            }         
        }
    }

    if (ball_count != 1 || hole_count != 1)
    {
        this->currentErrorMessage = "To many or\nno balls or holes";
        return false;
    }

    if (this->textbox.getString().empty())
    {
        this->currentErrorMessage = "Add a name \nto your map!";
        return false;
    }

    return true;
}

void Creator::saveMap()
{
    std::string file_path = "..\\Maps\\" + this->textbox.getString() + ".txt";
    std::ofstream file(file_path);
    std::string ball_pos_x_string = std::to_string(static_cast<int>(this->ball_pos.x));
    std::string ball_pos_y_string = std::to_string(static_cast<int>(this->ball_pos.y));
    std::cout << ball_pos_x_string << " " << ball_pos_y_string << std::endl;

    if (this->ball_pos.x < 100.0)
    {
        if (this->ball_pos.x < 10.0)
        {
            ball_pos_x_string = "00" + ball_pos_x_string;
        }
        else
        {
            ball_pos_x_string = "0" + ball_pos_x_string;
        }
    }
    if (this->ball_pos.y < 100.0)
    {
        if (this->ball_pos.y < 10.0)
        {
            ball_pos_y_string = "00" + ball_pos_y_string;
        }
        else
        {
            ball_pos_y_string = "0" + ball_pos_y_string;
        }
    }

    std::string ball_pos_string = ball_pos_x_string + ball_pos_y_string;

    file << ball_pos_string;

    for (auto el : tiles)
    {
        if (el.getPosition().x == 0.0)
        {
            file << 'n';
        }

        switch (el.getType())
        {
        case 'g':
            file << 'g';
            break;
        case 's':
            file << 's';
            break;
        case 'a':
            file << 'a';
            break;
        case 'w':
            file << 'w';
            break;
        case 'h':
            file << 'h';
            break;
        case 'b':
            file << 'g';
            break;
        default:
            std::cerr << "Couldnt identify tile type" << std::endl;
            break;
        }
    }
    file.close();
}

char Creator::run(sf::RenderWindow& window)
{
    this->setView(window.getDefaultView());
    bool showMessageBox = false;

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

            if (!showMessageBox)
            {
                if (event.type == sf::Event::KeyPressed)
                {
                    sf::Keyboard::Key keycode = event.key.code;
                    if (keycode >= sf::Keyboard::A && keycode <= sf::Keyboard::Z)
                    {
                        char chr = static_cast<char>(keycode - sf::Keyboard::A + 'a');
                        this->textbox.appendString(chr);
                    }
                    if (keycode == sf::Keyboard::Key::Backspace)
                    {
                        this->textbox.backspace();
                    }
                }

                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
                    for (auto& el : icons)
                    {
                        if (el.isClicked(mouse_pos, &this->sound))
                        {
                            this->isElementChosen = true;
                            this->currentElementToPlace = el.getType();
                        }
                    }

                    sf::FloatRect bounds_save = this->saveButton.getGlobalBounds();
                    if (bounds_save.contains(static_cast<sf::Vector2f>(mouse_pos)))
                    {
                        this->sound.play();
                        if (validateMap(window.getSize().x, window.getSize().y))
                        {
                            saveMap();
                            return 's';
                        }
                        else
                        {
                            showMessageBox = true;
                        }
                    }

                    sf::FloatRect bounds_back = this->backButton.getGlobalBounds();
                    if (bounds_back.contains(static_cast<sf::Vector2f>(mouse_pos)))
                    {
                        this->sound.play();
                        return 'c';
                    }

                    if (this->isElementChosen)
                    {
                        calculateMousePosGrid(mouse_pos, window);
                        placeOnScreen();
                    }
                }
            }
            else
            {
                MessageBox messageBox(this->currentErrorMessage, "OK", window.getSize().x, window.getSize().y);
                messageBox.run(window);
                showMessageBox = false;
            }
        }

        //drawing and displaying
        window.clear(sf::Color::Black);
        this->draw(window);
        window.display();
    }
	return 'c';
}

#include "Creator.h"
#include<iostream>


void Creator::makeIcons()
{
    std::vector<char> types = { 'g', 's', 'w', 'a', 'h', 'b' };
    for (int i = 0; i < types.size(); i++)
    {
        this->icons.emplace_back(Tile(sf::Vector2f(80.0+ i * 100.0, 0.0), types[i]));
        this->icons[i].setTexture(&this->textures[i]);
    }
}

void Creator::loadTextures()
{
    this->textures.emplace_back(loadTexture("D:\\studia\\Programowanie Strukturalne i Obiektowe\\Minigolf\\Textures\\grass_light.jpg"));
    this->textures.emplace_back(loadTexture("D:\\studia\\Programowanie Strukturalne i Obiektowe\\Minigolf\\Textures\\sand.jpg"));
    this->textures.emplace_back(loadTexture("D:\\studia\\Programowanie Strukturalne i Obiektowe\\Minigolf\\Textures\\wall.jpg"));
    this->textures.emplace_back(loadTexture("D:\\studia\\Programowanie Strukturalne i Obiektowe\\Minigolf\\Textures\\water.jpg"));
    this->textures.emplace_back(loadTexture("D:\\studia\\Programowanie Strukturalne i Obiektowe\\Minigolf\\Textures\\hole.png"));
    this->textures.emplace_back(loadTexture("D:\\studia\\Programowanie Strukturalne i Obiektowe\\Minigolf\\Textures\\ball_on_grass_light.png"));
    this->textures.emplace_back(loadTexture("D:\\studia\\Programowanie Strukturalne i Obiektowe\\Minigolf\\Textures\\save_icon.png"));
}

void Creator::makeText()
{
    std::vector<std::string> strings = { "Grass", "Sand", "Wall", "Water", "Hole", "Ball" };
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
        text.setPosition(sf::Vector2f(i*100.0 + text_offset_x, text_offset_y));
        menuText.emplace_back(text);
    }
}

Creator::Creator(int windowSizeX, int windowSizeY)
{
    this->isElementChosen = false;
    this->loadTextures();
    if (!this->font.loadFromFile("D:\\studia\\Programowanie Strukturalne i Obiektowe\\Minigolf\\Fonts\\BarlowSemiCondensed-Bold.ttf"))
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
    this->saveButton.setPosition(sf::Vector2f(windowSizeX - this->gridSize, 0.0));
    this->makeGrid(windowSizeX, windowSizeY);
}

void Creator::makeGrid(int windowSizeX, int windowSizeY)
{
    // initialize values

    int columns = windowSizeX/ this->gridSize;
    int rows = windowSizeY / this->gridSize + 1;
    int numLines = rows + columns - 2;
    this->grid.setPrimitiveType(sf::Lines);
    this->grid.resize(2 * (numLines));
    auto size = this->getView().getSize();

    // row separators
    for (int i = 0; i < rows - 1; i++)
    {
        int r = i + 1;
        float rowY = this->gridSize * r;
        this->grid[i * 2].position = { 0, rowY };
        this->grid[i * 2 + 1].position = { size.x, rowY };
    }

    // column separators
    for (int i = rows - 1; i < numLines; i++)
    {
        int c = i - rows + 2;
        float colX = this->gridSize * c;
        this->grid[i * 2].position = { colX, 0 };
        this->grid[i * 2 + 1].position = { colX, size.y };
    }
}

void Creator::draw(sf::RenderWindow& window)
{
    window.setView(getView());
    window.draw(grid);

    window.draw(this->menuBackground);
    window.draw(this->saveButton);
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
    Tile tile = Tile(tile_pos, this->currentElementToPlace);
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

char Creator::run(sf::RenderWindow& window)
{
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
                sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
                for (auto& el : icons)
                {
                    if (el.isClicked(mouse_pos))
                    {
                        this->isElementChosen = true;
                        this->currentElementToPlace = el.getType();
                    }
                }

                sf::FloatRect bounds = this->saveButton.getGlobalBounds();
                if (bounds.contains(static_cast<sf::Vector2f>(mouse_pos)))
                {
                    //make sure the map is valid
                    // if not show message whats wrong
                    //save map
                    return 's';
                }

                if (this->isElementChosen)
                {
                    calculateMousePosGrid(mouse_pos, window);
                    placeOnScreen();
                }
            }
        }

        //drawing and displaying
        window.clear(sf::Color::Black);
        this->draw(window);
        window.display();
    }
	return 'c';
}

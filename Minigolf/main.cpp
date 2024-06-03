#include<iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include"Screen.h"
#include"Map.h"
#include"TitleScreen.h"
#include"Creator.h"


int main()
{
    int windowSizeX = 800;
    int windowSizeY = 450;
    float gridSize = 20.0;
    sf::RenderWindow window(sf::VideoMode(windowSizeX, windowSizeY), "Minigolf");
    window.setFramerateLimit(60);

    std::unique_ptr<Screen> currentScreen = std::make_unique<TitleScreen>(windowSizeX, windowSizeY);
    char button = currentScreen->run(window);

    switch (button)
    {
    case 'p':
        //move to level-choosing menu
        currentScreen = std::make_unique<Map>(windowSizeX, windowSizeY, "textmap", gridSize);
        currentScreen->run(window);
        //show score
        //back to title screen
        break;
    case 'c':
        currentScreen = std::make_unique<Creator>(windowSizeX, windowSizeY, gridSize);
        currentScreen->run(window);
        //back to title screen
        break;
    default:
        std::cerr << "Unidenified button clicked" << std::endl;
    }

    return 0;
}
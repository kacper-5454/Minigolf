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

    std::unique_ptr<Screen> currentScreen;
    char button;

    while (window.isOpen())
    {
        currentScreen = std::make_unique<TitleScreen>(windowSizeX, windowSizeY);
        button = currentScreen->run(window);

        switch (button)
        {
        case 'p':
            // Move to level-choosing menu
            currentScreen = std::make_unique<Map>(windowSizeX, windowSizeY, "easy", gridSize);
            currentScreen->run(window);
            // Back to title screen after level choosing
            break;
        case 'c':
            currentScreen = std::make_unique<Creator>(windowSizeX, windowSizeY, gridSize);
            currentScreen->run(window);
            break;
        default:
            std::cerr << "Unidentified button clicked" << std::endl;
            break;
        }
    }

    return 0;
}
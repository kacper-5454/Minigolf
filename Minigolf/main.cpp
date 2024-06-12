#include<iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include"Screen.h"
#include"Map.h"
#include"TitleScreen.h"
#include"Creator.h"
#include"Menu.h"

int main()
{
    int windowSizeX = 800;
    int windowSizeY = 450;
    sf::RenderWindow window(sf::VideoMode(windowSizeX, windowSizeY), "Minigolf");
    window.setFramerateLimit(60);

    std::unique_ptr<Screen> currentScreen;
    std::string return_text;

    while (window.isOpen())
    {
        currentScreen = std::make_unique<TitleScreen>(windowSizeX, windowSizeY);
        return_text = currentScreen->run(window);

        if (return_text == "play")
        {
            currentScreen = std::make_unique<Menu>(windowSizeX, windowSizeY);
            return_text = currentScreen->run(window);
            if (return_text != "back")
            {
                currentScreen = std::make_unique<Map>(windowSizeX, windowSizeY, return_text);
                currentScreen->run(window);
            }
            
        }
        else if (return_text == "create")
        {
            currentScreen = std::make_unique<Creator>(windowSizeX, windowSizeY);
            currentScreen->run(window);
        }
    }

    return 0;
}
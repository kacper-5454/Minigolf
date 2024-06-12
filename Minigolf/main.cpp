#include<iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include"Screen.h"
#include"Map.h"
#include"TitleScreen.h"
#include"Creator.h"
#include"Menu.h"

void make_music(sf::Music& music)
{
    if (!music.openFromFile("..\\Sounds\\intro_music.wav"))
    {
        std::cerr << "Couldnt load intro music" << std::endl;
    }
    music.setLoop(true);
}

int main()
{
    int windowSizeX = 800;
    int windowSizeY = 450;
    sf::RenderWindow window(sf::VideoMode(windowSizeX, windowSizeY), "Minigolf", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);

    sf::Music music;
    make_music(music);
    music.play();

    std::unique_ptr<Screen> currentScreen;
    std::string return_text;

    while (window.isOpen())
    {
        currentScreen = std::make_unique<TitleScreen>(window);
        music.setVolume(25);
        return_text = currentScreen->run(window);

        if (return_text == "play")
        {
            currentScreen = std::make_unique<Menu>(window);
            music.setVolume(6);
            return_text = currentScreen->run(window);

            if (return_text != "back")
            {
                currentScreen = std::make_unique<Map>(return_text, window);
                currentScreen->run(window);
            }
            
        }
        else if (return_text == "create")
        {
            currentScreen = std::make_unique<Creator>(window);
            music.setVolume(6);
            currentScreen->run(window);
        }
    }

    return 0;
}
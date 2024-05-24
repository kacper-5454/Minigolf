#include<iostream>
#include"Map.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include<fstream>
#include<sstream>
#include"TitleScreen.h"
#include"Screen.h"


int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 450), "Minigolf");

    std::unique_ptr<Screen> currentScreen = std::make_unique<TitleScreen>();

    char button = currentScreen->run(window);
    switch (button)
    {
    case 'p':
        currentScreen = std::make_unique<Map>("D:\\studia\\Programowanie Strukturalne i Obiektowe\\Minigolf\\map.txt");
        currentScreen->run(window);
        //move to level-choosing menu
        break;
    case 'c':
        //move to create mode
        break;
    default:
        std::cerr << "Unidenified button clicked" << std::endl;
    }

    return 0;
}
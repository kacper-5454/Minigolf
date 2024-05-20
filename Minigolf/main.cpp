#include<iostream>
#include"Map.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include<fstream>
#include<sstream>


int main()
{
    Map map = Map("D:\\studia\\Programowanie Strukturalne i Obiektowe\\Minigolf\\map.txt", 20.0);

    sf::RenderWindow window(sf::VideoMode(map.getWidth(), map.getHeight()), "Minigolf");

    sf::Clock clock;
    sf::Time elapsed;

    while (window.isOpen())
    {
        elapsed = clock.restart();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);

        map.draw(window);

        window.display();
    }
    return 0;
}
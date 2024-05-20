#include "Grass.h"

Grass::Grass(sf::Vector2f position) :
	Background("D:\\studia\\Programowanie Strukturalne i Obiektowe\\Minigolf\\Textures\\grass_medium.jpg", position)
{
	friction = 0.25;
}

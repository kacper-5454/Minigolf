#include "Sand.h"

Sand::Sand(sf::Vector2f position) :
	Background("D:\\studia\\Programowanie Strukturalne i Obiektowe\\Minigolf\\Textures\\grass_dark.jpg", position)
{
	friction = 0.5;
}

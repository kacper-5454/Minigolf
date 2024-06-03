#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
class Tile : public sf::RectangleShape
{
private:
	sf::Texture texture;
	char type;
public:
	Tile(sf::Vector2f, char, float);
	void draw_icon(sf::RenderWindow&);
	bool isClicked(sf::Vector2i);
	char getType();
    struct Comparator
    {
        auto operator()(const Tile& a, const Tile& b) const
        {
            sf::Vector2f posA = a.getPosition();
            sf::Vector2f posB = b.getPosition();

            if (posA.y != posB.y) {
                return posA.y < posB.y;
            }

            if (posA.x != posB.x) {
                return posA.x < posB.x;
            }

            return false; // They are at the same position
        }
    };
};


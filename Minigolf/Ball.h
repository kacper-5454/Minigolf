#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Ball : public sf::CircleShape
{
private:
	sf::Texture texture;
	float speed =0;
	bool isMoving = false;
	bool isDragging = false;
	sf::Vector2f direction = sf::Vector2f(0.0, 0.0);
public:
	Ball(sf::Vector2f);
	Ball();
	void update_status();
	void release(sf::RenderWindow&);
	void move_ball(float, float);
};

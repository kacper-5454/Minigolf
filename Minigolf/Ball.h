#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include"Arrow.h"

class Ball : public sf::CircleShape
{
private:
	sf::Texture texture;
	float speed =0;
	float friction = 0.0;
	bool isMoving = false;
	bool isDragging = false;
	sf::Vector2f direction = sf::Vector2f(0.0, 0.0);
	Arrow arrow;
	sf::Vector2f last_position = sf::Vector2f(0.0, 0.0);
public:
	Ball(sf::Vector2f);
	Ball() = default;
	void update_status(sf::RenderWindow&);
	void release(sf::RenderWindow&);
	void move_ball(float);
	void draw_ball(sf::RenderWindow&);
	void calculateDirectionAndSpeed(sf::RenderWindow&);
	void setFriction(float);
	void setDirection(sf::Vector2f);
	sf::Vector2f getDirection();
	float getSpeed();
	sf::Vector2f getLastPosition();
	void setMoving(bool);
};

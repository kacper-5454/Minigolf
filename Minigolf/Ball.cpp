#include "Ball.h"
#include<iostream>

Ball::Ball(sf::Vector2f initial_position)
{
    if (!this->texture.loadFromFile("D:\\studia\\Programowanie Strukturalne i Obiektowe\\Minigolf\\Textures\\grass_dark.jpg"))
    {
        std::cerr << "Couldnt load ball texture" << std::endl;
    }
    else
    {
        this->setTexture(&this->texture);  
    }
    this->setRadius(5.0);
	this->setPosition(initial_position);
}

Ball::Ball() {}

void Ball::update_status()
{
    if (!this->isMoving)
    {
        this->isDragging = true;
    }
}

void Ball::release(sf::RenderWindow& window)
{
    if (this->isDragging)
    {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        sf::Vector2f mousePositionF(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
        this->direction = this->getPosition() - mousePositionF;
        this->speed = std::sqrt(direction.x * direction.x + direction.y * direction.y) * 10.0; // Adjust speed factor as needed
        if (this->speed > 0.0f)
        {
            direction /= std::sqrt(direction.x * direction.x + direction.y * direction.y); // Normalize direction
        }
        this->isDragging = false;
        this->isMoving = true;
    }
}

void Ball::move_ball(float time, float friction)
{
    if (this->isMoving)
    {
        this->move(this->direction * this->speed * time);
        this->speed -= friction * time; // Apply friction
        if (speed < 0.0f)
        {
            this->speed = 0.0f;
            this->isMoving = false;
        }
    }
}

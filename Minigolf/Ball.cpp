#include "Ball.h"
#include<iostream>

Ball::Ball(sf::Vector2f initial_position, sf::Texture* tex)
{
    this->setRadius(7.0);
	this->setPosition(initial_position);
    this->setFillColor(sf::Color::White);
    this->setOutlineColor(sf::Color::Black);
    this->setOutlineThickness(-2.0);
    this->arrow.setArrowTexture(tex);
    this->arrow.update(initial_position, this->direction, this->speed, this->getRadius());
    this->last_position = initial_position;
}

void Ball::calculateDirectionAndSpeed(sf::RenderWindow& window)
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    sf::Vector2f mousePositionF(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
    this->direction = this->getPosition() - mousePositionF;
    this->speed = std::sqrt(direction.x * direction.x + direction.y * direction.y) * 5.0; // Adjust speed factor as needed
    if (this->speed > 0.0f)
    {
        direction /= std::sqrt(direction.x * direction.x + direction.y * direction.y); // Normalize direction
    }
}

void Ball::update_status(sf::RenderWindow& window)
{
    if (!this->isMoving)
    {
        calculateDirectionAndSpeed(window);
        this->isDragging = true;
        this->arrow.update(this->getPosition(), this->direction, this->speed, this->getRadius());
    }
}

void Ball::release(sf::RenderWindow& window)
{
    if (this->isDragging)
    {
        calculateDirectionAndSpeed(window);
        this->isDragging = false;
        this->isMoving = true;
        this->last_position = this->getPosition();
    }
}

void Ball::move_ball(float time)
{
    if (this->isMoving)
    {
        this->move(this->direction * this->speed * time);
        this->speed -= this->friction * time; // Apply friction
        if (speed < 0.0f)
        {
            this->speed = 0.0f;
            this->isMoving = false;
        }
    }
}

void Ball::draw_ball(sf::RenderWindow& window)
{
    window.draw(*this);
    if (this->isDragging)
    {
        this->arrow.draw(window);
    }
}

void Ball::setFriction(float fr)
{
    this->friction = fr;
}

void Ball::setDirection(sf::Vector2f dir)
{
    this->direction = dir;
}

sf::Vector2f Ball::getDirection()
{
    return this->direction;
}

float Ball::getSpeed()
{
    return this->speed;
}

sf::Vector2f Ball::getLastPosition()
{
    return this->last_position;
}

void Ball::setMoving(bool iM)
{
    this->isMoving = iM;
}

bool Ball::getMoving()
{
    return this->isMoving;
}
#include "Background_element.h"
#include"Background_type.h"

Background_element::Background_element(Background_type tp, sf::Vector2f position, float size)
{
    this->setPosition(position);
    this->setSize(sf::Vector2f(size, size));
    this->type = tp;
}

Background_type Background_element::getType()
{
    return this->type;
}
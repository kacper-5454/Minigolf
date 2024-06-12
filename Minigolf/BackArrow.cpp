#include "BackArrow.h"
#include<iostream>
#include"MessageBox.h"

BackArrow::BackArrow(sf::Vector2f position, sf::RenderWindow& window)
{
	if (this->texture.loadFromFile("..\\Textures\\back_arrow.png"))
	{
		this->setTexture(&this->texture);
	}
	else
	{
		MessageBox messageBox("Couldn't load BackArrow texture", "OK", window);
		messageBox.run(window);
		window.close();
	}
	this->setSize(sf::Vector2f(20.0, 20.0));
	this->setPosition(position);

	if (this->buffer.loadFromFile("..\\Sounds\\button_click.wav"))
	{
		this->sound.setBuffer(this->buffer);
	}
	else
	{
		MessageBox messageBox("Couldn't load BackArrow sound buffer", "OK", window);
		messageBox.run(window);
		window.close();
	}
}

bool BackArrow::isClicked(sf::Vector2f mouse_pos)
{
	sf::FloatRect bounds = this->getGlobalBounds();
	if (bounds.contains(mouse_pos))
	{
		this->sound.play();
		return true;
	}
	else
	{
		return false;
	}
}

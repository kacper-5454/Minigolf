#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
class Screen : public sf::RectangleShape
{
private:
	sf::View view;
public:
	virtual ~Screen() = default;
	virtual std::string run(sf::RenderWindow& window) = 0;
	sf::Texture loadTexture(std::string);
	void handleResize(const sf::RenderWindow& window);
	sf::View getView();
	void setView(sf::View);
};


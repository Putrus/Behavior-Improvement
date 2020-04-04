#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "TextureManager.h"
class Platform{
private:
	int type;
	sf::Sprite* sprite;
	sf::RectangleShape* shape;
protected:
public:
	Platform(float width, float height);
	Platform(float width, float height, sf::Color color);
	Platform(std::string name, int type);


	void display(sf::RenderWindow& window);


	sf::Vector2f getPosition();
	sf::FloatRect getGlobalBounds();


	void setPosition(sf::Vector2f position);
	void setPosition(float x, float y);
};
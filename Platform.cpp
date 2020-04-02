#include "Platform.h"




Platform::Platform(float width, float height) {
	this->shape = new sf::RectangleShape();
	this->shape->setSize(sf::Vector2f(width, height));
	this->type = 0;
	this->sprite = NULL;
}

Platform::Platform(float width, float height, sf::Color color) {
	this->shape = new sf::RectangleShape();
	this->shape->setSize(sf::Vector2f(width, height));
	this->type = 0;
	this->sprite = NULL;
	this->shape->setFillColor(color);
}


Platform::Platform(std::string name){
	this->sprite = new sf::Sprite();
	this->sprite->setTexture(*TextureManager::getTexture(name + ".png"));
	this->type = 1;
	this->shape = NULL;
}




void Platform::display(sf::RenderWindow & window)
{
	if (this->type == 0)
	{
		window.draw(*this->shape);
	}
	else if (this->type == 1)
	{
		window.draw(*this->sprite);
	}
}




//getters
sf::Vector2f Platform::getPosition() {

	if (this->type == 0)
	{
		return this->shape->getPosition();
	}
	else if (this->type == 1)
	{
		return this->sprite->getPosition();
	}

}

sf::FloatRect Platform::getGlobalBounds() {

	if (this->type == 0)
	{
		return this->shape->getGlobalBounds();
	}
	else if (this->type == 1)
	{
		return this->sprite->getGlobalBounds();
	}

}



//setters
void Platform::setPosition(sf::Vector2f position)
{
	if (this->type == 0)
	{
		this->shape->setPosition(position);
	}
	else if (this->type == 1)
	{
		this->sprite->setPosition(position);
	}

}


void Platform::setPosition(float x, float y)
{
	this->setPosition(sf::Vector2f(x, y));
}
#include "Platform.h"




Platform::Platform(float width, float height) {
	this->shape = new sf::RectangleShape();
	this->shape->setSize(sf::Vector2f(width, height));
	this->shape->setFillColor(sf::Color::Black);
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


Platform::Platform(std::string name, int type){
	this->sprite = new sf::Sprite();
	this->sprite->setTexture(*TextureManager::getTexture(name + ".png"));
	this->type = 1;
	this->shape = NULL;


	int t, a, b, c, d;
	std::fstream file("Data/Platform/" + name + ".txt", std::ios::in);
	
	while(!file.eof())
	{
		file >> t >> a >> b >> c >> d;
		if (t == type)
		{
			this->sprite->setTextureRect(sf::IntRect(a, b, c, d));
			break;
		}
	}
	file.close();

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